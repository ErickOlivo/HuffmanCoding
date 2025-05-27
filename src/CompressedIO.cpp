#include "CompressedIO.h"
#include "HuffmanUtils.h"    // readFileToString() and deleteTree()
#include "frequency.h"
#include "HuffmanTree.h"
#include "HuffmanCodes.h"
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"

#include <fstream>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <cstring>           // std::memcmp

using namespace huffman;
using namespace huffman::util;

static constexpr char MAGIC[4] = { 'H','U','F','0' };

bool util::writeCompressedFile(const std::string& inputPath,
                               const std::string& compressedPath)
{
    /* 1. Read whole input (binary) */
    std::string data = readFileToString(inputPath);

    /* 2. Build Huffman */
    auto freqMap  = computeFrequencies(data);
    HuffmanNode* root = buildHuffmanTree(freqMap);
    auto  codes   = generateHuffmanCodes(root);
    std::string bitstr = encodeText(data, codes);

    /* 3. Pack bits -> bytes (MSB-first) */
    uint64_t bitCount = bitstr.size();
    size_t   byteCount = (bitCount + 7) / 8;
    std::vector<uint8_t> buffer(byteCount, 0);
    for (uint64_t i = 0; i < bitCount; ++i)
        if (bitstr[i] == '1')
            buffer[i / 8] |= uint8_t(1 << (7 - (i % 8)));

    /* 4. Write header + table + payload */
    std::ofstream out(compressedPath, std::ios::binary);
    if (!out) { deleteTree(root); return false; }

    /* 4.1 magic */
    out.write(MAGIC, 4);

    /* 4.2 unique-symbol count */
    uint32_t uniq = static_cast<uint32_t>(freqMap.size());
    out.write(reinterpret_cast<char*>(&uniq), sizeof(uniq));

    /* 4.3 symbol table */
    for (auto const& [ch, freq] : freqMap) {
        out.put(ch);
        uint32_t f = static_cast<uint32_t>(freq);
        out.write(reinterpret_cast<char*>(&f), sizeof(f));
    }

    /* 4.4 total bit-count */
    out.write(reinterpret_cast<char*>(&bitCount), sizeof(bitCount));

    /* 4.5 payload */
    out.write(reinterpret_cast<char*>(buffer.data()),
              static_cast<std::streamsize>(buffer.size()));

    deleteTree(root);
    return static_cast<bool>(out);
}

bool util::readCompressedFile(const std::string& compressedPath,
                              const std::string& outputPath)
{
    std::ifstream in(compressedPath, std::ios::binary);
    if (!in) return false;

    /* 1. verify magic */
    char magic[4];
    in.read(magic, 4);
    if (in.gcount() != 4 || std::memcmp(magic, MAGIC, 4) != 0)
        return false;

    /* 2. unique count */
    uint32_t uniq;
    in.read(reinterpret_cast<char*>(&uniq), sizeof(uniq));
    if (!in) return false;

    /* 3. frequency table */
    std::unordered_map<char,int> freqMap;
    for (uint32_t i = 0; i < uniq; ++i) {
        char ch = in.get();
        uint32_t f;
        in.read(reinterpret_cast<char*>(&f), sizeof(f));
        if (!in) return false;
        freqMap[ch] = static_cast<int>(f);
    }

    /* 4. bit-count */
    uint64_t bitCount;
    in.read(reinterpret_cast<char*>(&bitCount), sizeof(bitCount));
    if (!in) return false;

    /* 5. payload bytes */
    size_t byteCount = (bitCount + 7) / 8;
    std::vector<uint8_t> buffer(byteCount);
    in.read(reinterpret_cast<char*>(buffer.data()),
            static_cast<std::streamsize>(byteCount));
    if (!in) return false;

    /* 6. unpack bits to string */
    std::string bits;
    bits.reserve(bitCount);
    for (uint64_t i = 0; i < bitCount; ++i) {
        bool b = (buffer[i / 8] & (1 << (7 - (i % 8)))) != 0;
        bits.push_back(b ? '1' : '0');
    }

    /* 7. rebuild tree & decode */
    HuffmanNode* root = buildHuffmanTree(freqMap);
    std::string decoded = decodeText(bits, root);
    deleteTree(root);

    /* 8. write output */
    std::ofstream out(outputPath, std::ios::binary);
    if (!out) return false;
    out.write(decoded.data(),
              static_cast<std::streamsize>(decoded.size()));
    return static_cast<bool>(out);
}

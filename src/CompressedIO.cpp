#include "CompressedIO.h"
#include "HuffmanUtils.h"
#include "frequency.h"
#include "HuffmanTree.h"
#include "HuffmanCodes.h"
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"

#include <fstream>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <cstdint>
#include <cstring>  // <-- SOLUCIÓN AL memcmp

using namespace huffman;
using namespace huffman::util;

static constexpr char MAGIC[4] = { 'H','U','F','0' };

bool util::writeCompressedFile(const std::string& inputPath,
                               const std::string& compressedPath)
{
    // 1. Read whole input
    std::string data = readFileToString(inputPath);

    // 2. Compute frequencies, build tree, generate codes, encode bits
    auto freqMap = computeFrequencies(data);
    auto root    = buildHuffmanTree(freqMap);
    auto codes = generateHuffmanCodes(root);
    std::string bitstr = encodeText(data, codes);

    // 3. Pack bits into bytes (MSB-first)
    uint64_t bitCount = bitstr.size();
    size_t   byteCount = (bitCount + 7) / 8;
    std::vector<uint8_t> buffer(byteCount, 0);
    for (uint64_t i = 0; i < bitCount; ++i) {
        if (bitstr[i] == '1') {
            buffer[i/8] |= uint8_t(1 << (7 - (i % 8)));
        }
    }

    // 4. Write header + table + payload
    std::ofstream out(compressedPath, std::ios::binary);
    if (!out) return false;

    // magic
    out.write(MAGIC, 4);

    // unique count
    uint32_t uniq = uint32_t(freqMap.size());
    out.write(reinterpret_cast<char*>(&uniq), sizeof(uniq));

    // symbol table
    for (auto const& [ch, freq] : freqMap) {
        out.put(ch);
        uint32_t f = uint32_t(freq);
        out.write(reinterpret_cast<char*>(&f), sizeof(f));
    }

    // bit-count
    out.write(reinterpret_cast<char*>(&bitCount), sizeof(bitCount));

    // payload
    out.write(reinterpret_cast<char*>(buffer.data()), buffer.size());
    return bool(out);
}

bool util::readCompressedFile(const std::string& compressedPath,
                              const std::string& outputPath)
{
    std::ifstream in(compressedPath, std::ios::binary);
    if (!in) return false;

    // 1. Verify magic
    char magic[4];
    in.read(magic, 4);
    if (in.gcount() != 4 || std::memcmp(magic, MAGIC, 4) != 0)
        return false;

    // 2. Read unique count
    uint32_t uniq;
    in.read(reinterpret_cast<char*>(&uniq), sizeof(uniq));
    if (!in) return false;

    // 3. Read table
    std::unordered_map<char, int> freqMap;
    for (uint32_t i = 0; i < uniq; ++i) {
        char ch = in.get();
        uint32_t f;
        in.read(reinterpret_cast<char*>(&f), sizeof(f));
        if (!in) return false;
        freqMap[ch] = int(f);
    }

    // 4. Read bit-count
    uint64_t bitCount;
    in.read(reinterpret_cast<char*>(&bitCount), sizeof(bitCount));
    if (!in) return false;

    // 5. Read payload bytes
    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(in)),
                                 std::istreambuf_iterator<char>());

    // 6. Unpack bits into a string of '0'/'1'
    std::string bits;
    bits.reserve(bitCount);
    for (uint64_t i = 0; i < bitCount; ++i) {
        uint8_t byte = buffer[i/8];
        bool bit = (byte & (1 << (7 - (i % 8)))) != 0;
        bits.push_back(bit ? '1' : '0');
    }

    // 7. Rebuild tree, decode, write to file
    auto root    = buildHuffmanTree(freqMap);
    std::string decoded = decodeText(bits, root);
    std::ofstream out(outputPath, std::ios::binary);
    if (!out) return false;
    out << decoded;
    return bool(out);
}

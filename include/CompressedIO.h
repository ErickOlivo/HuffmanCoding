#pragma once
#include <string>

namespace huffman {
namespace util {

/**
 * @brief Compress a file into our custom Huffman-binary format.
 *
 * @param inputPath      Path to the original file to compress.
 * @param compressedPath Path where to write the compressed file (.huf).
 * @return true on success, false on any I/O error.
 */
bool writeCompressedFile(const std::string& inputPath,
                         const std::string& compressedPath);

/**
 * @brief Decompress a file from our custom Huffman-binary format.
 *
 * @param compressedPath Path to the compressed .huf file.
 * @param outputPath     Path where to write the decompressed bytes.
 * @return true on success, false on format or I/O error.
 */
bool readCompressedFile(const std::string& compressedPath,
                        const std::string& outputPath);

}  // namespace util
}  // namespace huffman

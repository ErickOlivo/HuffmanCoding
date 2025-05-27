#pragma once
#include <string>

namespace huffman {
namespace util {

/**
 * @brief Write a Huffman-compressed binary file.
 *
 * Format:
 *   • 4-byte magic:               'H','U','F','0'
 *   • uint32_t  unique symbol count
 *   • for each symbol:
 *       – char     symbol (1 byte)
 *       – uint32_t frequency (4 bytes)
 *   • uint64_t  total bit-count of payload
 *   • payload: bits packed MSB first into bytes, padded with zeros
 *
 * @param inputPath      Path to the original file to compress.
 * @param compressedPath Path where to write the compressed file.
 * @return true on success, false on I/O error.
 */
bool writeCompressedFile(const std::string& inputPath,
                         const std::string& compressedPath);


/**
 * @brief Read a Huffman-compressed binary file and write the decompressed data.
 *
 * Reads the header as in writeCompressedFile, rebuilds the tree,
 * unpacks the bitstream, decodes it, and writes the original bytes
 * to outputPath.
 *
 * @param compressedPath Path to the compressed file.
 * @param outputPath     Path where to write the decompressed file.
 * @return true on success, false on error (I/O or format).
 */
bool readCompressedFile(const std::string& compressedPath,
                        const std::string& outputPath);

}  // namespace util
}  // namespace huffman

# Huffman Coding - Advanced Programming Project

This is a C++ implementation of the **Huffman Coding** algorithm, developed as part of the Advanced Programming course.

The project includes:

- Frequency analysis of characters in a given text.
- Construction of a Huffman Tree using a priority queue.
- Generation of binary codes for each character.
- Encoding of the input text using the generated codes.
- Decoding of the binary string using the Huffman Tree.
- Memory management to free all dynamically allocated nodes.

---

## 🧠 What is Huffman Coding?

Huffman Coding is a lossless data compression algorithm. It assigns variable-length binary codes to characters based on their frequencies — characters that occur more frequently receive shorter codes.

---

## 🚀 Features

- Modular design with separate components:
  - Frequency module
  - Tree builder
  - Code generator
  - Encoder
  - Decoder
  - Memory cleanup
- Uses modern C++ (C++17)
- Clean, readable code with clear documentation
- `Makefile` included for easy compilation

---

## ⚙️ Compilation

To compile the project, simply run:

```bash
make
make clean

---

## 🧪 Example Output
For the input string "abracadabra", the program outputs:

Original text:     abracadabra
Character: 'a' - Frequency: 5
Character: 'b' - Frequency: 2
Character: 'r' - Frequency: 2
Character: 'c' - Frequency: 1
Character: 'd' - Frequency: 1

Huffman Tree successfully built. Total frequency: 11

Huffman Codes:
Character: 'a' => 0
Character: 'b' => 110
Character: 'r' => 10
Character: 'c' => 1110
Character: 'd' => 1111

Encoded text:      01101001110011110110100
Decoded text:      abracadabra
Decoding successful: The decoded text matches the original.

```


---

## 1  Build & Run

| Step | Command | Notes |
|------|---------|-------|
| **Compile** | `make` | Produces an executable named **`main`** (set `TARGET` in `Makefile` to rename). |
| **Clean**   | `make clean` | Removes objects & executable. |

> **Dependencies:** a C++17 compiler (e.g. `g++` 11+), GNU Make, optional **Graphviz** (`dot`) for tree-to-SVG export.

---

## 2  Command-line Usage

```text
./main -h
  -c <input> <output.huf>   Compress file
  -d <input.huf> <output>   Decompress file
  --tree                    (add after -c) export Huffman tree as tree.dot [+ tree.svg if dot is found]
```

### Examples

```bash
# Compress and generate an SVG of the tree
./main -c samples/sample_short.txt short.huf --tree

# Decompress
./main -d short.huf restored.txt

# Verify round-trip
diff samples/sample_short.txt restored.txt   # → no output means identical
```

If you invoke `./main` **with no flags**, a didactic demo runs on the hard-coded text *“abracadabra”*.

---

## 3  Compressed-file Format (`*.huf`)

| Offset | Size | Field | Description |
|--------|------|-------|-------------|
| 0      | 4 B  | Magic | **`48 55 46 30`** = “HUF0” |
| 4      | 4 B  | `uint32` **N** | Number of distinct symbols |
| 8      | 5 × N B | Symbol table | For each symbol *i*: <br>• 1 B   char<br>• 4 B  `uint32` frequency |
|…       | 8 B  | `uint64` bitcount | Total bits in payload |
|…       | ceil(bits/8) B | Bit payload | Data encoded MSB-first, zero-padded to whole bytes |

This header is self-sufficient: the frequency table lets the decoder rebuild the **exact same** deterministic Huffman tree.

---

## 4  Benchmark 📊

| File | Size (bytes) | Compressed (.huf) | Reduction |
|------|-------------:|------------------:|----------:|
| `samples/sample_short.txt` | 156 | 94 | **40 %** |
| `samples/sample_medium.txt`| 297 | 168 | **43 %** |
| *abracadabra* (demo)       | 11  |  3 | **73 %** |

*Hardware:* GitHub Codespace (2 vCPU).  
*Method:* `time ./main -c <file> out.huf`.

Compression and decompression each complete in **< 1 ms** for files under 1 kB—dominated by I/O.

---

## 5  Project Structure

```text
include/    Public headers
src/        Implementation
samples/    Test texts
Makefile    Single-command build
```

---

## 6  Graphviz Tree Export

Running the `--tree` flag alongside `-c` writes:

* `tree.dot` – Graphviz source  
* `tree.svg` – rendered automatically if **Graphviz** is installed (fallback: run `dot -Tsvg tree.dot -o tree.svg`).

![Huffman tree screenshot](docs/screenshot_tree.svg)


---

## 📌 Requirements
- C++17-compatible compiler (e.g., g++)

- GNU Make

---

## 📚 References
D.A. Huffman, “A Method for the Construction of Minimum-Redundancy Codes,” Proceedings of the IRE, 1952.

---

## 👨‍💻 Author
This project was developed by a Computer Science student for academic purposes.

---

## 📝 License
This project is open-source and available under the MIT License.

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

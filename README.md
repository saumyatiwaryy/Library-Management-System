📘 **Huffman++ - Huffman Compression and Decompression** 📚

Huffman++ is a C++ library that provides efficient Huffman compression and decompression functionalities. The library uses the Huffman algorithm to compress data by creating a variable-length prefix coding for characters based on their frequencies. This results in shorter codes for frequently occurring characters, leading to reduced file sizes.

📝 **How it works**

The library consists of two main files:
- `encode.cpp`: This file is used to compress data. It takes an input file and produces a compressed `.huf` file.
- `decode.cpp`: This file is used to decompress a compressed `.huf` file back to the original data.

The `huffman.hpp` header file contains the `huffman` class, which handles the creation of the Huffman tree, encoding, and decoding processes.

🛠️ **Usage**

To compress a file, run the following command in the terminal:
```
g++ encode.cpp huffman.cpp -o encode
./encode input_file.txt output_file.huf
```

To decompress a file, run the following command in the terminal:
```
g++ decode.cpp huffman.cpp -o decode
./decode input_file.huf output_file.txt
```

🔧 **Requirements**

The library requires a C++ compiler and the standard C++ library. No additional dependencies are needed.

📂 **File Structure**

- `encode.cpp`: Source code for the compression process.
- `decode.cpp`: Source code for the decompression process.
- `huffman.hpp`: Header file containing the `huffman` class declaration.
- `huffman.cpp`: Source code implementing the functions of the `huffman` class.



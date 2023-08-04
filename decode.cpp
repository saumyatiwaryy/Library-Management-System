#include <iostream>
#include "huffman.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided.
    // In this case, you expect two arguments: the name of the compressed file and the name of the output file.
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <compressed_file> <output_file>" << endl;
        exit(1);
    }

    // Create an instance of the Huffman class with the input and output file names.
    // The Huffman class likely handles the decompression logic.
    huffman f(argv[1], argv[2]);

    // Call the decompress() method of the Huffman class to perform the decompression process.
    // This method reads the compressed file, decodes the Huffman codes, and writes the original data to the output file.
    f.decompress();

    // Print a success message to indicate that the decompression process completed successfully.
    cout << "Decompressed successfully" << endl;

    return 0;
}
//The main function acts as the entry point of the program. It takes command-line arguments argv and the number of arguments argc. In this case, it expects two arguments: the name of the compressed file and the name of the output file.

The program creates an instance of the huffman class, passing the names of the input and output files. This huffman class is likely defined in the huffman.hpp header file and implemented in the huffman.cpp file. The huffman class likely contains methods for decompression, among other Huffman coding-related functionalities.

Finally, the main function calls the decompress() method of the huffman class to start the decompression process. Upon successful decompression, the program prints a message indicating that the process was completed successfully.

Overall, the decode.cpp program is responsible for handling the decompression of files compressed using Huffman coding, utilizing the functionalities provided by the huffman class.

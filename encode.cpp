#include <iostream>
#include "huffman.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided.
    // In this case, you expect two arguments: the name of the input file and the name of the compressed output file.
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <input_file> <compressed_output_file>" << endl;
        exit(1);
    }

    // Create an instance of the Huffman class with the input and compressed output file names.
    // The Huffman class likely handles the compression logic.
    huffman f(argv[1], argv[2]);

    // Call the compress() method of the Huffman class to perform the compression process.
    // This method reads the input file, generates Huffman codes, and writes the compressed data to the output file.
    f.compress();

    // Print a success message to indicate that the compression process completed successfully.
    cout << "Compressed successfully" << endl;

    return 0;
}
###The main function acts as the entry point of the program. It takes command-line arguments argv and the number of arguments argc. In this case, it expects two arguments: the name of the input file and the name of the compressed output file.

The program creates an instance of the huffman class, passing the names of the input and compressed output files. This huffman class is likely defined in the huffman.hpp header file and implemented in the huffman.cpp file. The huffman class likely contains methods for compression, among other Huffman coding-related functionalities.

Finally, the main function calls the compress() method of the huffman class to start the compression process. Upon successful compression, the program prints a message indicating that the process was completed successfully.

Overall, the encode.cpp program is responsible for handling the compression of files using Huffman coding, utilizing the functionalities provided by the huffman class.

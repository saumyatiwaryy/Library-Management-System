// Header Guards to prevent header files from being included multiple times
#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <string>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

// Defining Huffman Tree Node
struct Node {
    char data;
    unsigned freq;
    string code;
    Node* left, * right;

    // Constructor to initialize left and right pointers to NULL
    Node() {
        left = right = NULL;
    }
};

class huffman {
private:
    vector<Node*> arr; // Vector of tree nodes representing characters' ASCII values and their frequencies.

    fstream inFile, outFile; // File streams for reading and writing files.

    string inFileName, outFileName; // Input and output file names.

    Node* root; // Pointer to the root of the Huffman tree.

    // Comparator class for priority queue to arrange nodes based on frequency.
    class Compare {
    public:
        bool operator()(Node* l, Node* r) {
            return l->freq > r->freq;
        }
    };

    priority_queue<Node*, vector<Node*>, Compare> minHeap; // Min heap of nodes based on frequency.

    // Initializing a vector of tree nodes representing characters' ASCII values and initializing their frequency with 0.
    void createArr();

    // Traversing the constructed tree to generate Huffman codes for each present character.
    void traverse(Node*, string);

    // Function to convert a binary string to its equivalent decimal value.
    int binToDec(string);

    // Function to convert a decimal number to its equivalent binary string.
    string decToBin(int);

    // Reconstructing the Huffman tree while decoding the file.
    void buildTree(char, string&);

    // Creating Min Heap of Nodes by frequency of characters in the input file.
    void createMinHeap();

    // Constructing the Huffman tree.
    void createTree();

    // Generating Huffman codes.
    void createCodes();

    // Saving Huffman Encoded File.
    void saveEncodedFile();

    // Saving Decoded File to obtain the original File.
    void saveDecodedFile();

    // Reading the file to reconstruct the Huffman tree.
    void getTree();

public:
    // Constructor
    huffman(string inFileName, string outFileName) {
        this->inFileName = inFileName;
        this->outFileName = outFileName;
        createArr();
    }

    // Compressing the input file.
    void compress();

    // Decompressing the input file.
    void decompress();
};

#endif // HUFFMAN_HPP

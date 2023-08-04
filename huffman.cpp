#include "huffman.hpp"

// Initialize the array of nodes for characters and their frequencies.
// Each node represents a character with its frequency initialized to zero.
void huffman::createArr() {
    for (int i = 0; i < 128; i++) {
        arr.push_back(new Node());
        arr[i]->data = i;
        arr[i]->freq = 0;
    }
}

// Recursive function to traverse the Huffman tree and assign binary codes to each leaf node.
void huffman::traverse(Node* r, string str) {
    if (r->left == NULL && r->right == NULL) {
        r->code = str;
        return;
    }

    traverse(r->left, str + '0');
    traverse(r->right, str + '1');
}

// Convert a binary string to its equivalent decimal integer.
int huffman::binToDec(string inStr) {
    int res = 0;
    for (auto c : inStr) {
        res = res * 2 + c - '0';
    }
    return res;
}

// Convert a decimal integer to its equivalent 8-bit binary string.
string huffman::decToBin(int inNum) {
    string temp = "", res = "";
    while (inNum > 0) {
        temp += (inNum % 2 + '0');
        inNum /= 2;
    }
    res.append(8 - temp.length(), '0');
    for (int i = temp.length() - 1; i >= 0; i--) {
        res += temp[i];
    }
    return res;
}

// Build the Huffman tree based on the character code and path in the tree.
void huffman::buildTree(char a_code, string& path) {
    Node* curr = root;
    for (int i = 0; i < path.length(); i++) {
        if (path[i] == '0') {
            if (curr->left == NULL) {
                curr->left = new Node();
            }
            curr = curr->left;
        }
        else if (path[i] == '1') {
            if (curr->right == NULL) {
                curr->right = new Node();
            }
            curr = curr->right;
        }
    }
    curr->data = a_code;
}

// Create a Min Heap (priority queue) based on the character frequencies in the input file.
void huffman::createMinHeap() {
    char id;
    inFile.open(inFileName, ios::in);
    inFile.get(id);
    // Incrementing frequency of characters that appear in the input file.
    while (!inFile.eof()) {
        arr[id]->freq++;
        inFile.get(id);
    }
    inFile.close();
    // Pushing the Nodes which appear in the file into the priority queue (Min Heap).
    for (int i = 0; i < 128; i++) {
        if (arr[i]->freq > 0) {
            minHeap.push(arr[i]);
        }
    }
}

// Create the Huffman tree using the Min Heap (priority queue) created earlier.
void huffman::createTree() {
    Node* left, * right;
    priority_queue <Node*, vector<Node*>, Compare> tempPQ(minHeap);
    while (tempPQ.size() != 1)
    {
        left = tempPQ.top();
        tempPQ.pop();

        right = tempPQ.top();
        tempPQ.pop();

        root = new Node();
        root->freq = left->freq + right->freq;

        root->left = left;
        root->right = right;
        tempPQ.push(root);
    }
}

// Create binary codes for each character in the Huffman tree by traversing it.
void huffman::createCodes() {
    traverse(root, "");
}

// Save the compressed output file (.huf) with the meta-data (Huffman tree) and encoded content.
void huffman::saveEncodedFile() {
    inFile.open(inFileName, ios::in);
    outFile.open(outFileName, ios::out | ios::binary);
    string in = "";
    string s = "";
    char id;

    // Save the meta-data (Huffman tree) by encoding its structure and code for each character.
    in += (char)minHeap.size();
    priority_queue <Node*, vector<Node*>, Compare> tempPQ(minHeap);
    while (!tempPQ.empty()) {
        Node* curr = tempPQ.top();
        in += curr->data;
        // Save 16 decimal values representing the code of curr->data.
        s.assign(127 - curr->code.length(), '0');
        s += '1';
        s += curr->code;
        // Save decimal values of every 8-bit binary code.
        in += (char)binToDec(s.substr(0, 8));
        for (int i = 0; i < 15; i++) {
            s = s.substr(8);
            in += (char)binToDec(s.substr(0, 8));
        }
        tempPQ.pop();
    }
    s.clear();

    // Save codes of every character appearing in the input file.
    inFile.get(id);
    while (!inFile.eof()) {
        s += arr[id]->code;
        // Save decimal values of every 8-bit binary code.
        while (s.length() > 8) {
            in += (char)binToDec(s.substr(0, 8));
            s = s.substr(8);
        }
        inFile.get(id);
    }

    // Finally, if bits remaining are less than 8, append 0's.
    int count = 8 - s.length();
    if (s.length() < 8) {
        s.append(count, '0');
    }
    in += (char)binToDec(s);
    // Append count of appended 0's.
    in += (char)count;

    // Write the in string to the output file.
    outFile.write(in.c_str(), in.size());
    inFile.close();
    outFile.close();
}

// Save the decompressed output file after reading the compressed file and reconstructing the Huffman tree.
void huffman::saveDecodedFile() {
    inFile.open(inFileName, ios::in | ios::binary);
    outFile.open(outFileName, ios::out);
    unsigned char size;
    inFile.read(reinterpret_cast<char*>(&size), 1);
    // Reading count at the end of the file, which is the number of bits appended to make the final value 8-bit.
    inFile.seekg(-1, ios::end);
    char count0;
    inFile.read(&count0, 1);
    // Ignoring the meta-data (Huffman tree) (1 + 17 * size) and reading the remaining file.
    inFile.seekg(1 + 17 * size, ios::beg);

    vector<unsigned char> text;
    unsigned char textseg;
    inFile.read(reinterpret_cast<char*>(&textseg), 1);
    while (!inFile.eof()) {
        text.push_back(textseg);
        inFile.read(reinterpret_cast<char*>(&textseg), 1);
    }

    Node* curr = root;
    string path;
    for (int i = 0; i < text.size() - 1; i++) {
        // Converting decimal number to its equivalent 8-bit binary code.
        path = decToBin(text[i]);
        if (i == text.size() - 2) {
            path = path.substr(0, 8 - count0);
        }
        // Traversing the Huffman tree and appending the resultant data to the file.
        for (int j = 0; j < path.size(); j++) {
            if (path[j] == '0') {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }

            if (curr->left == NULL && curr->right == NULL) {
                outFile.put(curr->data);
                curr = root;
            }
        }
    }
    inFile.close();
    outFile.close();
}

// Retrieve the Huffman tree's meta-data from the compressed file and reconstruct the tree.
void huffman::getTree() {
    inFile.open(inFileName, ios::in | ios::binary);
    // Reading size of MinHeap.
    unsigned char size;
    inFile.read(reinterpret_cast<char*>(&size), 1);
    root = new Node();
    // Next size * (1 + 16) characters contain (char)data and (string)code [in decimal].
    for (int i = 0; i < size; i++) {
        char aCode;
        unsigned char hCodeC[16];
        inFile.read(&aCode, 1);
        inFile.read(reinterpret_cast<char*>(hCodeC), 16);
        // Converting decimal characters into their binary equivalent to obtain the code.
        string hCodeStr = "";
        for (int i = 0; i < 16; i++) {
            hCodeStr += decToBin(hCodeC[i]);
        }
        // Removing padding by ignoring first (127 - curr->code.length()) '0's and next '1' character.
        int j = 0;
        while (hCodeStr[j] == '0') {
            j++;
        }
        hCodeStr = hCodeStr.substr(j + 1);
        // Adding a node with aCode data and hCodeStr string to the Huffman tree.
        buildTree(aCode, hCodeStr);
    }
    inFile.close();
}

// Compress the input file by creating the Huffman tree, assigning codes, and saving the compressed file.
void huffman::compress() {
    createMinHeap();
    createTree();
    createCodes();
    saveEncodedFile();
}

// Decompress the compressed input file by reconstructing the Huffman tree and saving the decompressed file.
void huffman::decompress() {
    getTree();
    saveDecodedFile();
}
// Here's a brief overview of the functions and their roles:

1. **`createArr()`:**
   This function initializes an array `arr` of size 128, with each element representing a character. It sets the frequency of each character to 0.

2. **`traverse(Node* r, string str)`:**
   This function performs a recursive traversal of the Huffman tree to assign binary codes to each leaf node. The `code` member of each leaf node is set to the binary code obtained during the traversal.

3. **`binToDec(string inStr)`:**
   This function converts a binary string (`inStr`) to its equivalent decimal integer.

4. **`decToBin(int inNum)`:**
   This function converts a decimal integer (`inNum`) to its equivalent binary string.

5. **`buildTree(char a_code, string& path)`:**
   This function is used during the creation of the Huffman tree. It takes a character `a_code` and a binary string `path`. Based on the binary string, it constructs the corresponding path in the Huffman tree and adds the character node at the end of the path.

6. **`createMinHeap()`:**
   This function reads the input file and creates a priority queue (Min Heap) of nodes based on the frequency of characters in the input. The nodes with a non-zero frequency are pushed into the priority queue.

7. **`createTree()`:**
   This function builds the Huffman tree using the Min Heap created in the previous step. It repeatedly combines the two smallest frequency nodes from the priority queue to form a new parent node until there is only one node left in the priority queue, which becomes the root of the Huffman tree.

8. **`createCodes()`:**
   This function initiates the traversal of the Huffman tree to assign binary codes to each leaf node using the `traverse` function.

9. **`saveEncodedFile()`:**
   This function saves the compressed output file (`.huf`). It saves the meta-data (Huffman tree structure) followed by the encoded content of the input file.

10. **`saveDecodedFile()`:**
    This function reads the compressed input file (`.huf`) and decodes it using the Huffman tree. It then writes the original content back to the output file.

11. **`getTree()`:**
    This function retrieves the Huffman tree's meta-data from the compressed input file and reconstructs the tree.

12. **`compress()`:**
    This function coordinates the steps involved in compression. It calls functions to create the Huffman tree, assign codes, and save the compressed file.

13. **`decompress()`:**
    This function coordinates the steps involved in decompression. It reads the Huffman tree's meta-data from the compressed file, reconstructs the tree, and saves the decompressed output file.

The implementation demonstrates the core functionalities of Huffman coding, making it possible to compress and decompress files efficiently. Well done on implementing this essential data compression technique!

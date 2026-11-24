
#include <iostream>
using namespace std;

struct Node{
    char ch;
    int freq;
    Node* right;
    Node* left;

    Node(char c, int f){
        ch= c;
        freq = f;
        left = NULL;
        right = NULL;
    }
};

class MinHeap {
public:
    Node* heap[100];
    int n; //size of heap/ num of elements in heap

    MinHeap() {
        n = 0;
    }

    void swap(Node* a, Node* b){
        Node* temp = a;
        a=b;
        b=temp;
    }

    void insert(Node* node1){
        n++;
        int i=n;
        heap[i]=node1;
        while(i >1 && heap[i]->freq < heap[i/2]->freq){
            swap(heap[i],heap[i/2]);
            i=i/2;

        }
    }
    

    Node* removeMin() {
        Node* minimum = heap[1]; //first we store the root

        heap[1] = heap[n]; //assign root equal to the last node
        n--; //remove that last node

        int i = 1; 

        while (true) {
            int smallest = i;
            int left = 2*i;
            int right = 2*i + 1;

            if (left <= n && heap[left]->freq < heap[smallest]->freq)
                smallest = left;

            if (right <= n && heap[right]->freq < heap[smallest]->freq)
                smallest = right;

            if (smallest == i)
                break;

            swap(heap[i], heap[smallest]);
            i = smallest;
        }

        return minimum;
    }

    bool isEmpty() {
        return n == 0;
    }
};

Node* buildHuffmanTree(char S[], int f[], int n) {
    MinHeap h;

    // Insert all characters into min heap
    for (int i = 0; i < n; i++) {
        Node* temp = new Node(S[i], f[i]);
        h.insert(temp);
    }

    // Build Huffman tree
    while (h.n > 1) {
        Node* left = h.removeMin();
        Node* right = h.removeMin();

        Node* parent = new Node('$', left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        h.insert(parent);
    }

    return h.removeMin();
}

// Preorder traversal and print codes
void printCodes(Node* root, string code) {
    if (root == NULL)
        return;

    // Leaf node means we found a character
    if (root->left == NULL && root->right == NULL) {
        cout << root->ch << " : " << code << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {
    int n;

    cout << "Enter number of characters: ";
    cin >> n;

    char S[100];
    int f[100];

    cout << "Enter characters: ";
    for (int i = 0; i < n; i++)
        cin >> S[i];

    cout << "Enter frequencies: ";
    for (int i = 0; i < n; i++)
        cin >> f[i];

    Node* root = buildHuffmanTree(S, f, n);

    cout << "\nHuffman Codes (Preorder):\n";
    printCodes(root, "");

    return 0;
}

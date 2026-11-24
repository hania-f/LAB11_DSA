
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* heap[1000];
int n = 0;

// Insert node into min heap
void insert(Node* node) {
    n++;
    int i = n;

    while (i > 1 && heap[i / 2]->data > node->data) {
        heap[i] = heap[i / 2];
        i = i / 2;
    }

    heap[i] = node;
}

// Remove minimum node from heap
Node* removeMin() {
    Node* minNode = heap[1];
    Node* last = heap[n];

    n--;

    int i = 1;
    int child;

    while (i * 2 <= n) {
        child = i * 2;

        if (child + 1 <= n &&
            heap[child + 1]->data < heap[child]->data) {
            child++;
        }

        if (last->data <= heap[child]->data)
            break;

        heap[i] = heap[child];
        i = child;
    }

    heap[i] = last;

    return minNode;
}

// Merge K sorted linked lists
Node* mergeKLists(Node* lists[], int k) {

    n = 0;

    // Insert first node of every list
    for (int i = 0; i < k; i++) {
        if (lists[i] != NULL) {
            insert(lists[i]);
        }
    }

    Node* head = NULL;
    Node* tail = NULL;

    while (n > 0) {

        Node* smallest = removeMin();

        // Save next node before changing links
        Node* nextNode = smallest->next;

        // Add smallest node to answer list
        smallest->next = NULL;

        if (head == NULL) {
            head = smallest;
            tail = smallest;
        }
        else {
            tail->next = smallest;
            tail = smallest;
        }

        // Insert next node from same list
        if (nextNode != NULL) {
            insert(nextNode);
        }
    }

    return head;
}

// Display linked list
void display(Node* head) {
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
}

int main() {

    Node* lists[3];

    // List 1: 1 -> 4 -> 7
    lists[0] = new Node{1, new Node{4, new Node{7, NULL}}};

    // List 2: 2 -> 5 -> 8
    lists[1] = new Node{2, new Node{5, new Node{8, NULL}}};

    // List 3: 3 -> 6 -> 9
    lists[2] = new Node{3, new Node{6, new Node{9, NULL}}};

    Node* result = mergeKLists(lists, 3);

    cout << "Merged List: ";
    display(result);

    return 0;
}

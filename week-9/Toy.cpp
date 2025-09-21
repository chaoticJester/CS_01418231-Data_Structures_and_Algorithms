#include <iostream>
#include <cctype>
using namespace std;

typedef struct Node {
    int value;
    Node* rightChild;
    Node* leftChild;
} Node;

void createNode(Node** root, int value) {
    Node* node = new Node;
    node->value = value;
    node->rightChild = nullptr;
    node->leftChild = nullptr;

    if(*root == nullptr) {
        *root = node;
        return;
    }

    Node* current = *root;
    while(true) {
        if(value > current->value) {
            if(current->rightChild == nullptr) {
                current->rightChild = node;
                break;
            } 
            current = current->rightChild;
        } else {
            if(current->leftChild == nullptr) {
                current->leftChild = node;
                break;
            } 
            current = current->leftChild;
        }
    }
}

void ascendingPrint(Node* root) {
    if(root == nullptr) return;
    ascendingPrint(root->leftChild);
    cout << root->value << " ";
    ascendingPrint(root->rightChild);
}

void descendingPrint(Node* root) {
    if(root == nullptr) return;
    descendingPrint(root->rightChild);
    cout << root->value << " ";
    descendingPrint(root->leftChild);
}

bool search(Node* root, int number) {
    Node* current = root;
    while(current != nullptr) {
        if(number == current->value) return true;
        if(number > current->value) {
            current = current->rightChild;
        } else {
            current = current->leftChild;
        }
    }
    return false;
}

int treeDepth(Node* root) {
    if (root == nullptr) return 0;

    int leftDepth = treeDepth(root->leftChild);
    int rightDepth = treeDepth(root->rightChild);

    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

int main() {
    int n;
    cin >> n;

    Node* root = nullptr;
    int value;
    for(int i = 0; i < n; i++) {
        cin >> value;
        createNode(&root, value);
    }

    string command;
    while(cin >> command) {
        if(command == "e") {
            break;
        } else if(command == "s") {
            cout << "Ascending order: ";
            ascendingPrint(root);
            cout << "\n";
        } else if(command == "r") {
            cout << "Descending order: ";
            descendingPrint(root);
            cout << "\n";
        } else if(command == "f") {
            int number;
            while(cin >> number) {
                if(number == -111) break;
                if(search(root, number)) {
                    printf("Node %d is in the tree.\n", number);
                } else {
                    cout << "Node not found.\n";
                }
            }
        } else if(command == "d") {
            cout << "Depth: " << treeDepth(root) << "\n";
        } else {
            cout << "Unknown command.\n";
        }
    }

    return 0;
}
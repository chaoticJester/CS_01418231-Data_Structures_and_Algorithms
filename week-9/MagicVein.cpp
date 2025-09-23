#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

typedef struct Node {
    int amount;
    Node* left;
    Node* right;
} Node;

void addNode(Node** root, int amount) {
    Node* newNode = new Node;
    newNode->amount = amount;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if(*root == nullptr) {
        *root = newNode;
        return;
    }

    Node* current = *root;
    while(true) {
        if(amount > current->amount) {
            if(current->right == nullptr) {
                current->right = newNode;
                break;
            }
            current = current->right;
        } else {
            if(current->left == nullptr) {
                current->left = newNode;
                break;
            }
            current = current->left;
        }
    }
}

bool isPrime(int number) {
    if(number <= 1) return false;
    if(number == 2 || number == 3) return true;
    if(number % 2 == 0 || number % 3 == 0) return false;
    for(int i = 5; i*i <= number; i++) {
        if(number % i == 0 || number % (i+2) == 0) {
            return false;
        }
    }
    return true;
}

void possibleMining(Node* root, int x, int y, bool* found) {
    if(!root) return;

    possibleMining(root->left, x, y, found);

    if(root->amount > 0) {
        if( (root->amount >= x && root->amount <= y) ||
            (root->amount % 7 == 0) ||
            isPrime(root->amount) ) {
            cout << root->amount << " ";
            *found = true;
        }
    }

    possibleMining(root->right, x, y, found);
}

void deleteNode(Node* root) {
    if(root == nullptr) return;
    deleteNode(root->left);
    deleteNode(root->right);
    delete root;
}

int main() {
    int test_amount;
    cin >> test_amount;
    Node* root = nullptr;

    for(int i = 0; i < test_amount; i++) {
        int mining_point, amount, x, y;
        int min = 5000; 
        int max = -1;
        cin >> mining_point;
        
        for(int j = 0; j < mining_point; j++) {
            cin >> amount;
            if(amount > 0) {
                if(amount < min) {
                    min = amount;
                }
                if(amount > max) {
                    max = amount;
                }
            }
            addNode(&root, amount);
        }

        cin >> x >> y;
        if((x > max && y < min) || !root) {
            cout << "IMPOSSIBLE\n";
        } else {
            bool found = false;
            possibleMining(root, x, y, &found);
            if(!found) {
                cout << "IMPOSSIBLE";
            }
            cout << "\n";
        }
        deleteNode(root);
        root = nullptr;
    }

    return 0;
}
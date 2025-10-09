
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct Node {
    int value;
    Node* right;
    Node* left;
} Node;

void insertNode(int value, Node** root) {
    Node* node = new Node{value, nullptr, nullptr};

    if(!(*root)) {
        *root = node;
        return;
    }

    Node* current = *root;
    while(true) {
        if(value <= current->value) {
            if(current->left == nullptr) {
                current->left = node;
                break;
            }
            current = current->left;
        } else {
            if(current->right == nullptr) {
                current->right = node;
                break;
            }
            current = current->right;
        }
    }
}

void inorder(Node* root, vector<int>& arr) {
    if (root == nullptr) return;
    inorder(root->left, arr);
    arr.push_back(root->value);
    inorder(root->right, arr);
}

void postorder(Node* root, vector<int>& arr) {
    if (root == nullptr) return;
    postorder(root->left, arr);
    postorder(root->right, arr);
    arr.push_back(root->value);
}


void BSTToMaxHeap(Node* root, vector<int> &arr, int* i) {
    if (root == nullptr) return;
    BSTToMaxHeap(root->left, arr, i);
    BSTToMaxHeap(root->right, arr, i);
    root->value = arr[++*i];
}

void BFS(Node* root, vector<int>& heap) {
    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* n = q.front(); q.pop();
        heap.push_back(n->value);

        if(n->left) q.push(n->left);
        if(n->right) q.push(n->right);
    }
}

void convertToMaxHeap(Node* root, vector<int>& heap) {
    vector<int> arr;
    int i = -1;
    inorder(root, arr);
    BSTToMaxHeap(root, arr, &i);
    BFS(root, heap);
}

void heapify(vector<int> &v, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right  = 2 * i + 2;

    if(left < n && v[left] > v[largest]) {
        largest = left;
    }
    if(right < n && v[right] > v[largest]) {
        largest = right;
    }
    if(largest != i) {
        int tmp = v[i];
        v[i] = v[largest];
        v[largest] = tmp;
        heapify(v, n, largest);
    }
} 

void buildMaxHeap(vector<int> &v) {
    int n = v.size();
    for(int i = n/2 - 1; i >= 0; i--) {
        heapify(v, n, i);
    }
}


int main() {

    int all_tree;
    cin >> all_tree;

    int value;
    vector<int> result;
    for(int i = 0; i < all_tree; i++) {
        Node* root = nullptr;
        while(cin >> value) {
            if(value == -111) break;
            insertNode(value, &root);
        }
        vector<int> maxHeap;
        convertToMaxHeap(root, maxHeap);
        buildMaxHeap(maxHeap);
        for(int e : maxHeap) result.push_back(e);
        buildMaxHeap(result);
    }

    for(int i = 0; i < result.size(); i++) {
        cout << result[i];
        if(i < result.size() - 1) {
            cout << ",";
        } else {
            cout << "\n";
        }
    }

    return 0;
}
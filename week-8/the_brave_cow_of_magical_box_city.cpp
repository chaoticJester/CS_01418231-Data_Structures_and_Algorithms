#include <iostream>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {
    char* name;
    Node* parent = nullptr;
    vector<Node*> children;
};

unordered_map<string, Node*> existedItem;

bool isDescendant(Node* ancestor, Node* descendant) {
    while (descendant) {
        if (descendant == ancestor) {
            return true;
        }
        descendant = descendant->parent;
    }
    return false;
}

Node* findChild(Node* parent, Node* child) {
    if (!parent) return nullptr;
    for (Node* c : parent->children) {
        if (c == child) return c;
    }
    return nullptr;
}

void removeChild(Node* parent, Node* child) {
    if (!parent) return;
    for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
        if (*it == child) {
            parent->children.erase(it);
            return;
        }
    }
}

void moveNode(Node** root, Node* child, Node* newParent) {
    if (!child || child == newParent || isDescendant(child, newParent)) return;

    Node* oldParent = child->parent;
    if (oldParent) {
        removeChild(oldParent, child);
    } else {
        if (child == *root) {
            *root = nullptr;
        }
    }

    if (newParent) {
        newParent->children.push_back(child);
        child->parent = newParent;
    } else {
        if (*root == nullptr) {
            *root = child;
            child->parent = nullptr;
        } else {
            (*root)->parent = child;
            child->children.push_back(*root);
            *root = child;
            child->parent = nullptr;
        }
    }
}

void removeNodeAndDescendants(Node* target) {
    if (!target) return;
    for (Node* child : target->children) {
        removeNodeAndDescendants(child);
    }
    existedItem.erase(target->name); 
    delete[] target->name;
    delete target;
}

void printTree(Node* node, int depth = 0) {
    if (!node) return;

    if (depth > 0) {
        for (int i = 0; i < depth * 2 - 2; ++i) cout << " ";
        cout << "|_";
    }

    cout << node->name << "\n";

    for (Node* child : node->children) {
        printTree(child, depth + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Node* root = nullptr;
    string commandline;
    string command, item, parent;

    while (getline(cin, commandline)) {
        stringstream ss(commandline);
        ss >> command;

        if (command == "M") {
            ss >> item >> parent;
            Node* i = existedItem.count(item) ? existedItem[item] : nullptr;
            Node* p = existedItem.count(parent) ? existedItem[parent] : nullptr;

            if (i && item != parent) {
                if (parent == "NULL") {
                    moveNode(&root, i, nullptr);
                } else if (p && !isDescendant(i, p)) {
                    moveNode(&root, i, p);
                }
            }
        } else if (command == "R") {
            ss >> item;
            Node* i = existedItem.count(item) ? existedItem[item] : nullptr;
            if (i) {
                if (i->parent) removeChild(i->parent, i);
                else if (i == root) root = nullptr;
                removeNodeAndDescendants(i);
            }
        } else if (!command.empty()) {
            item = command;
            ss >> parent;
            if (!existedItem.count(item)) {
                Node* newNode = new Node;
                newNode->name = new char[item.size() + 1];
                strcpy(newNode->name, item.c_str());

                if (parent == "NULL") {
                    if (root == nullptr) {
                        root = newNode;
                        existedItem[item] = newNode;
                    } else {
                        existedItem[item] = newNode;
                        moveNode(&root, newNode, nullptr);
                    }
                } else if (existedItem.count(parent)) {
                    Node* p = existedItem[parent];
                    newNode->parent = p;
                    p->children.push_back(newNode);
                    existedItem[item] = newNode;
                }
            }
        } else {
            break;
        }
    }

    if (root) {
        printTree(root);
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}

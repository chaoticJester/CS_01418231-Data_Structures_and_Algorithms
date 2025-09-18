#include <iostream>
using namespace std;

typedef struct Node {
    string name;
    Node* parent;
    Node* leftChild;
    Node* rightSibling;
} Node;

Node* findNode(Node* root, string parent) {
    if(root == nullptr) {
        return nullptr;
    } 
    if(root->name == parent) {
        return root;
    }
    Node* found = findNode(root->leftChild, parent);

    if (found != nullptr) {
        return found;
    }

    return findNode(root->rightSibling, parent);
}

void createNode(Node** root, string item, Node* parent) {
    Node* newItem = new Node;
    newItem->name = item;
    newItem->parent = parent;
    newItem->leftChild = nullptr;
    newItem->rightSibling = nullptr;

    if(*root == nullptr) {
        *root = newItem;
        return;
    }
    if(parent != nullptr) {
        if(parent->leftChild != nullptr) {
            Node* child = parent->leftChild;
            while(child->rightSibling != nullptr) {
                child = child->rightSibling;
            }
            child->rightSibling = newItem;
        } else {
            parent->leftChild = newItem;
        }
    }
    
}

bool isDescendant(Node* parent, Node* child) {
    if (child == nullptr) return false;
    if (child->parent == parent) return true;
    return isDescendant(parent, child->parent);
}

void moveNode(Node** root, Node* child, Node* newParent) {
    if (child == nullptr || *root == nullptr) return;

    Node* oldParent = child->parent;
    if(oldParent != nullptr) {
        if(oldParent->leftChild == child) {
            oldParent->leftChild = child->rightSibling;
        } else {
            Node* sibling = oldParent->leftChild;
            while (sibling && sibling->rightSibling != child) {
                sibling = sibling->rightSibling;
            }
            if (sibling) {
                sibling->rightSibling = child->rightSibling;
            }
        }
    }

    child->rightSibling = nullptr;  
    child->parent = newParent;  

    if(newParent != nullptr) {
        if(newParent->leftChild == nullptr) {
            newParent->leftChild = child;
        } else {
            Node* sibling = newParent->leftChild;
            while (sibling->rightSibling != nullptr) {
                sibling = sibling->rightSibling;
            }
            sibling->rightSibling = child;
        }
    } else {
        if (*root != child) {
            Node* oldRoot = *root;
            if (!child->leftChild)
                child->leftChild = oldRoot;
            else {
                Node* last = child->leftChild;
                while (last->rightSibling) last = last->rightSibling;
                last->rightSibling = oldRoot;
            }
            oldRoot->parent = child;
            *root = child;
        }
    }
}

void removeNode(Node** root, Node* target) {
    if (target == nullptr || *root == nullptr) return;

    Node* child = target->leftChild;
    while (child) {
        Node* next = child->rightSibling;
        removeNode(root, child);
        child = next;
    }

    Node* parent = target->parent;
    if (parent) {
        if (parent->leftChild == target) {
            parent->leftChild = target->rightSibling;
        } else {
            Node* sibling = parent->leftChild;
            while (sibling && sibling->rightSibling != target)
                sibling = sibling->rightSibling;
            if (sibling) sibling->rightSibling = target->rightSibling;
        }
    }

    if (*root == target) {
        *root = nullptr;
    }

    delete target;
}

void printTree(Node* root, string indent = "", bool isLast = true) {
    if (!root) return;

    cout << indent;
    if (!root->parent) {
        cout << root->name << endl;
    } else {
        cout << "|_" << root->name << endl;
    }

    string childIndent = indent;
    if (root->parent) {
        childIndent += "  ";
    }

    Node* child = root->leftChild;
    while (child) {
        printTree(child, childIndent, child->rightSibling == nullptr);
        child = child->rightSibling;
    }
}


int main() {

    Node* root = nullptr;

    string item, parent;
    bool noError = true;
    while(cin >> item >> parent) {
        if(!item.empty() && !parent.empty()) {
            if(item == "M") {
                item = parent;
                cin >> parent;
                Node* i = findNode(root, item);
                Node* p = findNode(root, parent);
                if(i && !isDescendant(i, p)) {
                    moveNode(&root, i, p);
                }
            } else if(item == "R") {
                Node* target = findNode(root, parent);
                if(root == target) {
                    noError = false;
                }
                removeNode(&root, target);
            } else {
                Node* i = findNode(root, item);
                Node* p = findNode(root, parent);
                if(!i && (parent == "NULL" || p != nullptr)) {
                    createNode(&root, item, p);
                } else {
                    noError = false;
                    break;
                }
            }
        } else {
            noError = false;        
        }   
    }


    if(noError && root) {
        printTree(root);
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
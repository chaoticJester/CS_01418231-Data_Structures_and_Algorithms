#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

struct Name {
    string value;
    Name* right;
    Name* left;
};

struct Target {
    string value;
    Name* root;
};

string toLowercase(string input) {
    string result = input;
    for (char& c : result) {
        c = tolower((unsigned char)(c));  
    }
    return result;
}

bool isSameName(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++) {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i]))
            return false;
    }
    return true;
}

void createName(string name, vector<Target*>& mysticWell, bool isTarget) {
    if (isTarget) {
        Target* newT = new Target;
        newT->value = name;
        newT->root = nullptr;
        mysticWell.insert(mysticWell.begin(), newT);
        return;
    }

    Name* newName = new Name;
    newName->value = name;
    newName->left = nullptr;
    newName->right = nullptr;
    
    for (Target* target : mysticWell) {
        if (isSameName(name, target->value)) {
            if (target->root == nullptr) {
                target->root = newName;
                return;
            }
            Name* current = target->root;
            while (current != nullptr) {
                if (name < current->value) {
                    if (current->left == nullptr) {
                        current->left = newName;
                        return;
                    }
                    current = current->left;
                } else {
                    if (current->right == nullptr) {
                        current->right = newName;
                        return;
                    }
                    current = current->right;
                }
            }
            break;
        }
    }
}

void postOrderPrint(Name* name) {
    if(name == nullptr) return;

    postOrderPrint(name->left);
    cout << name->value << " ";
    postOrderPrint(name->right);
}

int main() {
    vector<Target*> mysticWell;
    string target;
    getline(cin, target);

    if(!target.empty()) {
        stringstream ss(target);
        string token;
        while (ss >> token) {
            bool sameName = false;
            for (Target* n : mysticWell) {
                if (isSameName(token, n->value)) {
                    sameName = true;
                    break;
                }
            }
            if (sameName) continue;
    
            createName(token, mysticWell, true);
        }
    }

    string input;
    while(getline(cin, target)) {
        if(target.empty()) continue;
        stringstream ss(target);
        ss >> input;
        createName(input, mysticWell, false);
    }


    if(mysticWell.empty()) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (Target* target : mysticWell) {
            if (target->root == nullptr) {
                cout << "\"" << toLowercase(target->value) << "\" is not found!\n";
            }
        }
        for(Target* target : mysticWell) {
            if(target->root != nullptr) {
                postOrderPrint(target->root);
                cout << "\n";
            }   
        }
    }

    return 0;
}
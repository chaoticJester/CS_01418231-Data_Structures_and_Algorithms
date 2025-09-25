#include <iostream>
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
    Target* right;
    Target* left; 
};

string toLowercase(string input) {
    string result = input;
    for (char& c : result) {
        c = tolower((unsigned char)(c));  
    }
    return result;
}

bool isSameName(string a, string b) {
    return toLowercase(a) == toLowercase(b);
}


void createTarget(string targetName, Target** mysticWell) {
    Target* newTarget = new Target;
    newTarget->value = toLowercase(targetName);
    newTarget->root = nullptr;
    newTarget->left = nullptr;
    newTarget->right = nullptr;
    
    if(*mysticWell == nullptr) {
        *mysticWell = newTarget;
        return;
    }

    Target* c = *mysticWell;
    Target* parent = nullptr;
    
    while(c != nullptr) {
        if(isSameName(c->value, newTarget->value)) { 
            delete newTarget; 
            return; 
        }
        
        parent = c;
        if(newTarget->value > c->value) {
            c = c->right;
        } else {
            c = c->left;
        }
    }
    
    if (newTarget->value > parent->value) {
        parent->right = newTarget;
    } else {
        parent->left = newTarget;
    }
}

void createName(string name, Target* mysticWell) {
    Name* newName = new Name;
    newName->value = name;
    newName->left = nullptr;
    newName->right = nullptr;
    
    
    while(mysticWell != nullptr) {
        if(isSameName(mysticWell->value, newName->value)) {
            if(mysticWell->root == nullptr) {
                mysticWell->root = newName;
                return ;
            }
            Name* currentName = mysticWell->root;
            while (true) {
                if (newName->value <= currentName->value) {
                    if (currentName->left == nullptr) {
                        currentName->left = newName;
                        return;
                    }
                    currentName = currentName->left;
                } else {
                    if (currentName->right == nullptr) {
                        currentName->right = newName;
                        return;
                    }
                    currentName = currentName->right;
                }
            }
        }
        if(mysticWell->value < toLowercase(newName->value)) {
            mysticWell = mysticWell->right;
        } else {
            mysticWell = mysticWell->left;
        }
    }
}


void inOrderPrint(Name* name) {
    if(name == nullptr) return;

    inOrderPrint(name->left);
    cout << name->value << " ";
    inOrderPrint(name->right);
}


void targetTraversal(Target* target) {
    if(target == nullptr) return;
    
    targetTraversal(target->right);
    if (target->root != nullptr) {
        inOrderPrint(target->root);
        cout << "\n";
    } else {
        cout << "\"" << target->value << "\"" << " is not found!\n";
    }
    targetTraversal(target->left);
}

int main() {
    Target* mysticWell = nullptr;
    string targetLine;
    getline(cin, targetLine);

    if (targetLine.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    stringstream ss(targetLine);
    string token;
    while (ss >> token) {
        createTarget(token, &mysticWell); 
    }

    string nameInput;
    while(getline(cin, nameInput)) { 
        if(nameInput.empty()) continue;
        createName(nameInput, mysticWell); 
    }

    Target* t = mysticWell;


    if (mysticWell == nullptr) {
        cout << "IMPOSSIBLE\n";
    } else {
        targetTraversal(mysticWell); 
    }


    return 0;
}
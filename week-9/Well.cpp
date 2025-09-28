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
    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = (char)tolower((unsigned char)input[i]);
    }
    return input;
}

void createTarget(string target, Target** mysticWell) {
    Target* newTarget = new Target;
    newTarget->value = toLowercase(target);
    newTarget->root = NULL;
    newTarget->left = NULL;
    newTarget->right = NULL;

    if(*mysticWell == NULL) {
        *mysticWell = newTarget;
        return;
    }

    Target* current = *mysticWell;
    while(true) {
        if(current->value == newTarget->value) {
            delete newTarget;
            return;
        } else if(current->value < newTarget->value) {
            if(current->right == NULL) {
                current->right = newTarget;
                return;
            }
            current = current->right;
        } else {
            if(current->left == NULL) {
                current->left = newTarget;
                return;
            }
            current = current->left;
        }
    }
}

void createName(string name, Target* mysticWell) {
    Name* newName = new Name;
    newName->value = name;
    newName->left = NULL;
    newName->right = NULL;

    Target* t = mysticWell;
    string lname = toLowercase(name);

    while(t != NULL) {
        if(lname == t->value) {
            if(t->root == NULL) {
                t->root = newName;
                return;
            }
            Name* current = t->root;
            while(true) {
                if(name <= current->value) {
                    if(current->right == NULL) {
                        current->right = newName;
                        return;
                    }
                    current = current->right;
                } else {
                    if(current->left == NULL) {
                        current->left = newName;
                        return;
                    }
                    current = current->left;
                }
            }
        }
        if(lname < t->value) {
            t = t->left;
        } else {
            t = t->right;
        }
    }
    delete newName;
}

void printName(Name* name, bool &first) {
    if(name == NULL) return;
    printName(name->right, first);
    if (!first) cout << " ";
    cout << name->value;
    first = false;
    printName(name->left, first);
}

void printTarget(Target* target) {
    if(target == NULL) return;
    printTarget(target->right);

    if(target->root) {
        bool first = true;
        printName(target->root, first);
    } else {
        cout << "\"" << target->value << "\" is not found!";
    }
    cout << "\n";

    printTarget(target->left);
}

int main() {
    Target* mysticWell = NULL;
    string firstLine;
    getline(cin, firstLine);

    if(firstLine.empty()) {
        cout << "IMPOSSIBLE\n";
    } else {
        stringstream ss(firstLine);
        string target;
        while(ss >> target) {
            createTarget(target, &mysticWell);
        }

        string nameLine, name;
        while(getline(cin, nameLine)) {
            stringstream ss(nameLine);
            if (ss >> name)
                createName(name, mysticWell);
        }

        printTarget(mysticWell);
    }
    return 0;
}
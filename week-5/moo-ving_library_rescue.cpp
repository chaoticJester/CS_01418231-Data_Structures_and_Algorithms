#include <iostream>
#include <vector>
#include <map>
#include <cctype>
using namespace std;

int countAscii(string bookName) {
    int sumAscii = 0;
    for(char c : bookName) {
        sumAscii += (int)c;
    }
    return sumAscii;
}

void sortBook(vector<string> &shelf) {
    int n = shelf.size();
    for (int i = 1; i < n; i++) {
        string key = shelf[i];
        int j = i - 1;
        while (j >= 0 && shelf[j] > key) {
            shelf[j + 1] = shelf[j];
            j--;
        }
        shelf[j + 1] = key;
    }
}

bool isValid(string bookName) {
    if(bookName.empty() || bookName.length() > 30 || !isValid(bookName) || !isalpha(bookName[0])) {
        return false;
    }
    for(char c : bookName) {
        int ascii = (int)c;
        if(ascii < 32 || ascii > 126) {
            return false;
        }
    }
    return true;
}

void printShelves(map<char, vector<vector<string>>> &shelves) {
    for(auto &shelf : shelves) {
        char shelfName = shelf.first;
        auto &bookList = shelf.second;
        printf("Shelf %c:\n", shelfName);

        for(int i = 0; i < bookList.size(); i++) {
            printf("%c%d: ", shelfName, i + 1);
            if(bookList[i].empty()) {
                printf("shelf is empty!\n");
                continue;
            }

            for(int j = 0; j < bookList[i].size(); j++) {
                cout << bookList[i][j];
                if(j < bookList[i].size() - 1) {
                    cout << " ";
                }
            }
            printf("\n");

        }
    }
}

int main() {
    int width;
    cin >> width;
    
    if(width >= 1 && width <= 255) {
        cin.ignore();
        map<char, vector<vector<string>>> shelves;
        
        string bookName;
        while(getline(cin, bookName)) {
            if(isValid(bookName)) {
                return 0;
            }   

            char shelfName = toupper(bookName[0]);
            int hashIndex = countAscii(bookName) % width;

            if(shelves[shelfName].empty()) {
                shelves[shelfName] = vector<vector<string>>(width);
            }
            shelves[shelfName][hashIndex].push_back(bookName);
        }

        for (auto &shelf : shelves) {
            for (int i = 0; i < width; i++) {
                sortBook(shelf.second[i]);  
            }
        }

        if(shelves.empty()) {
            printf("All shelfs are empty!\n");
        } else {
            printShelves(shelves);
        }
        
    }
    return 0;
}

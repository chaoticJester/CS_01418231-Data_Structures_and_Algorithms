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
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(shelf[j] > shelf[j + 1]) {
                string tmpBook = shelf[j];
                shelf[j] = shelf[j + 1];
                shelf[j + 1] = tmpBook;
            }
        }
    }
}


bool isValid(string name) {
    if(name.empty()) {
        return false;
    }
    if(!isalpha(name[0])) {
        return false;
    }
    for(char c : name) {
        int ascii = (int)c;
        if(ascii < 32 || ascii > 126) {
            return false;
        }
    }
    return true;
}

int main() {
    int width;
    cin >> width;
    cin.ignore();
    if(width < 256) {
        map<char, vector<vector<string>>> shelves;
        
        string bookName;
        bool isError = false;
        while(getline(cin, bookName)) {
            if(bookName.length() > 30 || !isValid(bookName)) {
                isError = true;
                return 0;
            }   
            char shelfName = bookName[0];
            int hashIndex = countAscii(bookName) % width;

            if(shelves[shelfName].empty()) {
                shelves[shelfName] = vector<vector<string>>(width);
            }
            shelves[shelfName][hashIndex].push_back(bookName);
        }

        if(!isError) {
            if(shelves.empty()) {
                cout << "All shelfs are empty!\n";
            } else {
                for(auto &subShelf : shelves) {
                    char shelfName = subShelf.first;
                    auto &bookList = subShelf.second;

                    printf("Shelf %c:\n", shelfName);

                    for(int i = 0; i < bookList.size(); i++) {
                        printf("%c%d: ", shelfName, i + 1);
                        if(bookList[i].empty()) {
                            printf("shelf is empty!\n");
                            continue;
                        }

                        sortBook(bookList[i]);
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
        }
    }
    return 0;
}

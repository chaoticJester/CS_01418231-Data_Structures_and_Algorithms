#include <iostream>
#include <vector>
#include <cctype>
#include <cstring>
#include <cstdlib> 
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int width;
    cin >> width;
    cin.ignore();
    if (width < 1 || width > 255) return 0;

    vector<vector<vector<char*>>> shelves(26, vector<vector<char*>>(width));

    string bookName;
    bool isThereABook = false;

    while (getline(cin, bookName)) {
        if (bookName.empty() || bookName.length() > 30 || !isalpha(bookName[0])) return 0;

        for (char c : bookName) {
            if ((int)c < 32 || (int)c > 126) return 0;
        }

        char* newBook = new char[bookName.length() + 1];
        strcpy(newBook, bookName.c_str());

        int shelfIndex = toupper(bookName[0]) - 'A';
        int sumAscii = 0;
        for (char c : bookName) sumAscii += (int)c;
        int hashIndex = sumAscii % width;

        shelves[shelfIndex][hashIndex].push_back(newBook);
        isThereABook = true;
    }

    if (!isThereABook) {
        printf("All shelfs are empty!\n");
    } else {
        for (int i = 0; i < 26; i++) {
            bool hasShelf = false;
            for (int j = 0; j < width; j++) {
                if (!shelves[i][j].empty()) {
                    hasShelf = true;
                    break;
                }
            }
            if (!hasShelf) continue;

            char label = 'A' + i;
            printf("Shelf %c:\n", label);
            for (int j = 0; j < width; j++) {
                printf("%c%d: ", label, j + 1);
                if (shelves[i][j].empty()) {
                    printf("shelf is empty!\n");
                } else {
                    for (int k = shelves[i][j].size() - 1; k >= 0; k--) {
                        printf("%s", shelves[i][j][k]);
                        if (k > 0) printf(" ");
                        delete[] shelves[i][j][k];  
                    }
                    printf("\n");
                }
            }
        }
    }

    return 0;
}

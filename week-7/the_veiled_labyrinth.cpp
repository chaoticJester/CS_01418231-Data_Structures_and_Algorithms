#include <iostream>
#include <vector>
using namespace std;

int rowChanges[] = {-1, 1, 0, 0};
int columnChanges[] = {0, 0, 1, -1};

//ใช้ DFS หาว่ามีทางออกที่เป็นไปได้หรือไม่
int findExit(int r, int c, int exit, int path, vector<vector<int>> &labyrinth, vector<vector<bool>> &visited) {
    //ถ้าช่องที่ r, c คือทางออก return true
    if(labyrinth[r][c] == exit) {
        return true;
    }

    //ให้ค่าของช่อง r,c (ช่องที่เดินทางมา) = true;
    visited[r][c] = true;

    //วนลูปหาทางที่เป็นไปได้ทั้ง 4 ทิศ
    for(int i = 0; i < 4; i++) {
        int rowPath = r + rowChanges[i];
        int columnPath = c + columnChanges[i];

        //ช่องไม่อยูู่ใน matrix[row][column] ก็ continue
        if(rowPath < 0 ||columnPath < 0 || rowPath >= labyrinth.size() || columnPath >= labyrinth[0].size()) {
            continue;
        }

        //ช่องเคยเดินไปแล้วก็ continue
        if(visited[rowPath][columnPath]) {
            continue;
        }

        //ช่องเดินทางไปได้ หรือช่องนั้นคือทางออกให้เรียกตัวเองต่อ
        if(labyrinth[rowPath][columnPath] == path || labyrinth[rowPath][columnPath] == exit) {
            if(findExit(rowPath, columnPath, exit, path, labyrinth, visited)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int row, column, start, exit, path, startRow, startColumn;
    cin >> row >> column;
    cin >> start >> exit;
    cin >> path;

    vector<vector<int>> labyrinth(row, vector<int>(column));

    for(int r = 0; r < row; r++) {
        for(int c = 0; c < column; c++) {
            cin >> labyrinth[r][c];
            if(labyrinth[r][c] == start) {
                startRow = r;
                startColumn = c;
            }
        }
    }

    vector<vector<bool>> visited(row, vector<bool>(column));

    if(findExit(startRow, startColumn, exit, path, labyrinth, visited)) {
        cout << "Real Labyrinth\n";
    } else {
        cout << "Faux Labyrinth\n";
    }

    return 0;
}
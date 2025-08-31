#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void findPath(int currentTower, int targetTower, vector<int> &currentPath, vector<bool> &visitedTower, vector<vector<int>> &towerGraph, int* allPaths, vector<int> &shortestPath) {
    currentPath.push_back(currentTower);
    visitedTower[currentTower] = true;

    if(currentTower == targetTower) {
        (*allPaths)++;
        if(shortestPath.empty() || currentPath.size() < shortestPath.size()) {
            shortestPath = currentPath;
        }
    }  else {
        for(int tower : towerGraph[currentTower]) {
            if(!visitedTower[tower]) {
                findPath(tower, targetTower, currentPath, visitedTower, towerGraph, allPaths, shortestPath);
            }
        }
    }

    visitedTower[currentTower] = false;
    currentPath.pop_back();
}

int main() {
    short towerAmount, pathAmount;
    cin >> towerAmount >> pathAmount;

    short from, to;
    vector<vector<int>> towerGraph(towerAmount);
    for(short i = 0; i < pathAmount; i++) {
        cin >> from >> to;
        towerGraph[from].push_back(to);
        towerGraph[to].push_back(from);
    }
    
    short start, end;
    cin >> start >> end;

    int allPath = 0;
    vector<int> currentPath;
    vector<bool> visited(towerAmount, false);
    vector<int> shortestPath;

    // ---- DFS หาจำนวนเส้นทางที่เป็นไปได้ และเก็บเส้นทางที่สั้นที่สุด ---- //
    findPath(start, end, currentPath, visited, towerGraph, &allPath, shortestPath);
    
    if(!allPath) {
        cout << "IMPOSSIBLE\n"; 
    } else {
        cout << allPath << "\n";
        for(short i = 0; i < shortestPath.size(); i++) {
            cout << shortestPath[i] << ((i < shortestPath.size() - 1) ? " " : "");
        }
    }

    return 0;
} 

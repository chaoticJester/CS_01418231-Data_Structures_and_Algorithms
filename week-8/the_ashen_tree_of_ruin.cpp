#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

void biteTheDust(unordered_map<int, vector<int>> &tree, int start) {
    queue<int> q;
    unordered_set<int> visited;
    
    q.push(start);
    visited.insert(start);
    
    while(!q.empty()) {
        int levelSize = q.size();
        for(int i = 0; i < levelSize; i++) {
            int node = q.front();
            cout << node << " ";
            q.pop();
            
            for(int child : tree[node]) {
                if(visited.find(child) == visited.end()) {
                    q.push(child);
                    visited.insert(child);
                }
            }
        }
        cout << "\n";
    }
}

int main() {
    int n;
    cin >> n;
    
    unordered_map<int, vector<int>> tree;
    
    int root;
    cin >> root;

    tree[root] = {};

    int parent, child;
    for(int i = 0; i < n-1; i++) {
        cin >> parent >> child;
        tree[parent].push_back(child);
        if(tree[child].size() != 0) {
            tree[child].insert(tree[child].begin(), parent);
        } else {
            tree[child].push_back(parent);
        }
    }

    int start;
    cin >> start;

    // for(auto &p : tree) {
    //     cout << p.first << ": ";
    //     for(int j : p.second) {
    //         cout << j << " ";
    //     }
    //     cout << "\n";
    // }

    biteTheDust(tree, start);

    return 0;
}
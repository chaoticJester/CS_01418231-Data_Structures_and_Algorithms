#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int> &v, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right  = 2 * i + 2;

    if(left < n && v[left] > v[largest]) {
        largest = left;
    }
    if(right < n && v[right] > v[largest]) {
        largest = right;
    }
    if(largest != i) {
        int tmp = v[i];
        v[i] = v[largest];
        v[largest] = tmp;
        heapify(v, n, largest);
    }
} 

void buildMaxHeap(vector<int> &v) {
    int n = v.size();
    for(int i = n/2 - 1; i >= 0; i--) {
        heapify(v, n, i);
    }
}

void heapSort(vector<int> &v) {
    int n = v.size();
    buildMaxHeap(v);

    for(int i = n - 1; i > 0; i--) {
        int tmp = v[0];
        v[0] = v[i];
        v[i] = tmp;
        heapify(v, i, 0);
    }
}

int main() {
    int size;
    cin >> size;
    
    vector<int> maxHeap;
    for(int i = 0; i < size; i++) {
        int orb;
        cin >> orb;
        maxHeap.push_back(orb);
        
    }

    heapSort(maxHeap);


    for(int i = size - 1; i >= 0; i--) {
        cout << maxHeap[i] << (i > 0? " " : "\n");
    }

    return 0;
}
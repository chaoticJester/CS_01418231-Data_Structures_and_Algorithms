#include <iostream>
#include <vector>
using namespace std;

typedef struct Customer {
    string name;
    int level;
    int order; 
} Customer;

bool greaterCustomer(const Customer &a, const Customer &b) {
    if (a.level != b.level) return a.level > b.level; 
    return a.order < b.order; 
}

void heapify(vector<Customer> &v, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && greaterCustomer(v[left], v[largest])) {
        largest = left;
    }
    if(right < n && greaterCustomer(v[right], v[largest])) {
        largest = right;
    }

    if(largest != i) {
        Customer tmp = v[i];
        v[i] = v[largest];
        v[largest] = tmp;
        heapify(v, n, largest);
    }
}

void buildMaxHeap(vector<Customer> &v) {
    int n = v.size();
    for(int i = n/2 - 1; i >= 0; i--) {
        heapify(v, n, i);
    }
}

void heapSort(vector<Customer> &v) {
    int n = v.size();
    buildMaxHeap(v);

    for(int i = n - 1; i > 0; i--) {
        Customer tmp = v[0];
        v[0] = v[i];
        v[i] = tmp;
        heapify(v, i, 0);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string kChok;
    string input, name;
    int level;
    int orderCounter = 0;

    vector<Customer> queue;

    while(cin >> name >> level) {
        Customer customer = {name, level, orderCounter++};
        queue.push_back(customer);
        kChok = customer.name;
    }

    if(queue.empty()) {
        cout << "IMPOSSIBLE\n";
    } else {
        heapSort(queue); 

        int q = 1;
        for(int i = 0; i < (int)queue.size(); i++, q++) {
            if(queue[i].name == kChok) {
                break;
            }
        }

        cout << "GET QUEUE : " << q << "\n";
    }
    return 0;
}

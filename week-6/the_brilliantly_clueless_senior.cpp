#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main() {

    vector<int> identifiers;
    int identifier;
    int target;
    
    //รับอินพุตมาจนกว่าจะหมดไฟล์
    while (cin >> identifier) {
        identifiers.push_back(identifier);
    }

    // pop เอาเลขสุดท้ายมาเป็นเลขที่ต้องการ
    target = identifiers[identifiers.size() - 1];
    identifiers.pop_back();


    //ใช้ binary search ค้นหา
    bool isFound = false;
    int compareCount = 0;
    int left = 0; 
    int right = identifiers.size() - 1; 
    while(left <= right) { 
        compareCount++; 
        int mid = (right + left) / 2; 
        if(identifiers[mid] == target) { 
            isFound = true;  
            break; 
        } else if(identifiers[mid] < target) { 
            left = mid + 1; 
        } else { 
            right = mid - 1; 
        } 
    }

    if(isFound) {
        cout << "Present - " << compareCount << endl;
    } else {
        cout << "Absent\n";
    }

    return 0;
}
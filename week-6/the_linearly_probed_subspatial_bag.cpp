#include <iostream>
#include <vector>
#include <cctype>

const int TABLE_SIZE = 20;

typedef struct {
    std::string name;
    float x, y, z;
} Item;

//ค้นหาของในกระเป๋า
void searchItem(std::vector<Item> &bag, std::string target) {
    Item *result = nullptr;

    //ค้นหาโดยใช้การ Hash มาช่วย 
    //หาไม่เจอในคราวแรกให้ค้นหาช่องถัดๆไปจนกว่าจะครบทุกช่อง
    for(int i = 0; i < TABLE_SIZE; ++i) {
        int currIndex = (target.length() + i) % TABLE_SIZE;
        if(bag[currIndex].name.empty()) {
            break;
        }
        if(bag[currIndex].name == target) {
            result = &bag[currIndex];
            break;
        }
    }

    if(result != nullptr) {
        printf("( %.2f, %.2f, %.2f )\n", result->x, result->y, result->z);
    } else {
        std::cout << "Item not found.\n";
    }
}

//ตรวจสอบเลขพิกัด
bool validPosi(float x) {
    return x >= 0.0 && x <= 10000.0;
}

//ตรวจสอบชื่อสิ่งของ
bool validName(std::string name) {
    if(name.length() > 20) {
        return false;
    }
    for(char c : name) {
        if(!isalpha(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<Item> bagOfHolding(TABLE_SIZE);
    std::string itemName;
    float x, y, z;
    int countItem = 0;

    while(true) {
        std::cin >> itemName;
        if(itemName == "--------------------") { 
            break;
        }
        std::cin >> x >> y >> z;

        //ถ้าของเก็บได้ให้เก็บโดยการใช้ Hash และ linear pruding
        if(countItem < TABLE_SIZE && validName(itemName) && validPosi(x) && validPosi(y) && validPosi(z)) {
            for(int i = 0; i < TABLE_SIZE; ++i) {
                int index = (itemName.length() + i) % TABLE_SIZE;
                if(bagOfHolding[index].name.empty()) {
                    bagOfHolding[index] = {itemName, x, y, z};
                    countItem++;
                    break;
                }
            }
        }
        
        //กระเป๋าเต็มไม่รับเพิ่ม
        if(countItem == TABLE_SIZE) {
            while(std::cin >> itemName && itemName != "--------------------");
            break;
        }
    }

    bagOfHolding.resize(TABLE_SIZE);

    std::string target;
    while(std::cin >> target) {
        searchItem(bagOfHolding, target);
    }

    return 0;
}

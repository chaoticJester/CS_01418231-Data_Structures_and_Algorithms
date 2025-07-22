#include <iostream>

struct Spell {
    short value;
    Spell *next;
};


// สร้าง Linked List โดยเอา node ใหม่ มาต่อหลัง head
void createLinkedList(Spell **head, int value) {
    Spell *newSpell = new Spell;
    newSpell->value = value;
    newSpell->next = *head;
    *head = newSpell;
}

// เช็คว่ามีค่า value ใน Linked List หลักหรือยัง
Spell *isInLinkedList(Spell *mainHead, int value) {
    while(mainHead != nullptr) {
        if(mainHead->value == value) {
            return mainHead;
        }
        mainHead = mainHead->next;
    }
    return nullptr;
}

//แทรก node ของ Linked List รอง ที่ value ไม่มีใน Linked List หลัก
//ใน Linked List หลัก 
void insertNode(Spell *mainHead, Spell *tmpHead) {
    Spell *insertPosition = isInLinkedList(mainHead, tmpHead->value);
    Spell *tmpCurrentHead = tmpHead;
    tmpHead = tmpHead->next;
    delete tmpCurrentHead;

    while(tmpHead != nullptr) {
        Spell *next = tmpHead->next;
        if(!isInLinkedList(mainHead, tmpHead->value)) {
            Spell *newNode = new Spell{tmpHead->value, insertPosition->next};
            insertPosition->next = newNode;
            insertPosition = newNode;
        }
        delete tmpHead;
        tmpHead = next;
    }
}

//cout ค่าของแต่ละ node ใน Linked List หลัก
//แล้วลบ node นั่นๆทิ้งไปด้วย
void printLinkedList(Spell **head) {
    Spell *current = *head;
    while(current != nullptr) {
        std::cout << current->value << " ";
        Spell *next = current->next;
        delete current;
        current = next;
    }
    *head = nullptr;
}


int main() {
    short n;
    std::cin >> n;

    Spell *mainHead = nullptr;

    //รับ input
    for (short i = 0; i < n; i++) {
        Spell *tmpHead = nullptr;
        int value;
        while(true) {
            std::cin >> value;
            //ถ้า value == 0 == หมดชุดเลข ก็ break
            if(value == 0) {
                break;
            }
            createLinkedList(&tmpHead, value);
        }
        if(i == 0) {
            //ถ้าเป็นรอบแรก
            mainHead = tmpHead;
        } else if (tmpHead != nullptr) {
            if (isInLinkedList(mainHead, tmpHead->value)) {
                // ถ้า value แรกของ Linked List รอง มีใน Linked List หลัก
                //แทรกทุก node ของ Linked List รอง ที่ value ไม่มีใน Linked List หลัก
                insertNode(mainHead, tmpHead);
            } else {
                // ถ้า value แรกไม่มี ลบทั้ง Linked List ทิ้ง
                while (tmpHead != nullptr) {
                    Spell* next = tmpHead->next;
                    delete tmpHead;
                    tmpHead = next;
                }
            }
        }
    }

    //แสดง value ของ node ใน Linked List หลัก
    printLinkedList(&mainHead);

    return 0;
}

#include <iostream>

struct Adventurer {
    int number;
    Adventurer* next;
};

void createCircularList(Adventurer** head, int adv_amount) {
    if (adv_amount <= 0) {
        *head = NULL;
        return;
    }

    Adventurer* newNode = (Adventurer*)malloc(sizeof(Adventurer));
    newNode->number = 1;
    *head = newNode;

    Adventurer* prev = newNode;
    for (int i = 2; i <= adv_amount; ++i) {
        Adventurer* temp = (Adventurer*)malloc(sizeof(Adventurer));
        temp->number = i;
        prev->next = temp;
        prev = temp;
    }
    prev->next = *head;  // ทำให้เป็นวงกลม
}

void arthurEatAdventurer(Adventurer** head, int adv_amount, int arthur_target) {
    Adventurer* curr = *head;
    Adventurer* prev = NULL;

    while (adv_amount > 0) {
        int step = (arthur_target - 1) % adv_amount; // ลดจำนวนก้าวให้น้อยลงโดย mod
        for (int i = 0; i < step; ++i) {
            prev = curr;
            curr = curr->next;
        }

        // curr คือคนที่ถูกเลือกออก
        std::cout << curr->number << " ";

        // ลบ curr ออกจากวงกลม
        if (curr == prev) { // คนเดียวเหลืออยู่
            free(curr);
            curr = NULL;
            *head = NULL;
            break;
        } else {
            prev->next = curr->next;
            Adventurer* temp = curr;
            curr = curr->next;
            free(temp);
        }
        adv_amount--;
    }
    std::cout << std::endl;
}

int main() {
    int adv_amount, arthur_target;
    std::cin >> adv_amount >> arthur_target;

    Adventurer* head = NULL;
    createCircularList(&head, adv_amount);
    arthurEatAdventurer(&head, adv_amount, arthur_target);

    return 0;
}
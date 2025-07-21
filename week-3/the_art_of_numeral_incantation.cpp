#include <iostream>

struct Spell {
    short value;
    Spell *next;
};

bool isInLinkedList(short value, Spell *head) {
    while (head != nullptr) {
        if (head->value == value) {
            return true;
        }
        head = head->next;
    }
    return false;
}

void createLinkedList(Spell **tmpHead, short value) {
    Spell *newSpell = new Spell{value, *tmpHead};
    *tmpHead = newSpell;
}

Spell *findNode(short value, Spell *head) {
    while (head != nullptr) {
        if (head->value == value) return head;
        head = head->next;
    }
    return nullptr;
}

void insertNode(Spell *head, Spell *tmpHead) {
    Spell *insertPoint = findNode(tmpHead->value, head);
    if (!insertPoint) return;

    Spell *current = tmpHead->next;
    Spell *tail = insertPoint;
    while (current != nullptr) {
        if (!isInLinkedList(current->value, head)) {
            Spell *newNode = new Spell{current->value, tail->next};
            tail->next = newNode;
            tail = newNode;
        }
        current = current->next;
    }
}

void freeLinkedList(Spell *head) {
    while (head != nullptr) {
        Spell *next = head->next;
        delete head;
        head = next;
    }
}

void inputSpell(Spell **head, short round) {
    short tmp;
    Spell *tmpHead = nullptr;
    while (std::cin >> tmp && tmp != 0) {
        if (!isInLinkedList(tmp, tmpHead)) {
            createLinkedList(&tmpHead, tmp);
        }
    }

    if (tmpHead != nullptr && round == 0) {
        *head = tmpHead;
    } else if (tmpHead != nullptr && *head != nullptr) {
        if (isInLinkedList(tmpHead->value, *head)) {
            insertNode(*head, tmpHead);
        }
        freeLinkedList(tmpHead); 
    }
}

void printLinkedList(Spell *head) {
    while (head != nullptr) {
        std::cout << head->value << " ";
        head = head->next;
    }
}

int main() {
    short n;
    std::cin >> n;

    Spell *head = nullptr;

    for (short i = 0; i < n; i++) {
        inputSpell(&head, i);
    }

    printLinkedList(head);
    freeLinkedList(head); 
    return 0;
}

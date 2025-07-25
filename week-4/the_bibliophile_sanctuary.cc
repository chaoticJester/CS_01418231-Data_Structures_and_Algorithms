#include <iostream>
#include <sstream>
#include <vector>
#include <string>

void printStatus(std::vector<std::string> books, std::vector<std::string> miena, std::vector<std::string> luna) {
    std::cout << "Miena's Remaining Book(s) to be read: ";
    if(miena.empty()) {
        std::cout << "None" << std::endl;
    } else {
        for(int i = 0; i < miena.size(); i++) {
            std::cout << miena[i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Luna's Remaining Book(s) to be read: ";
    if(luna.empty()) {
        std::cout << "None" << std::endl;
    } else {
        for(int i = 0; i < luna.size(); i++) {
            std::cout << luna[i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Remaining Book(s) in the Pile: ";
    if(books.empty()) {
        std::cout << "None" << std::endl;
    } else {
        for(int i = 0; i < books.size(); i++) {
            std::cout << books[i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "====================" << std::endl;
}

int main() {
    std::string input_line;
    std::vector<std::string> books;
    std::vector<std::string> miena_queue;
    std::vector<std::string> luna_queue;

    // รับชื่อหนังสือจากบรรทัดแรก
    std::getline(std::cin, input_line);
    std::stringstream ss(input_line);
    std::string book;

    while (ss >> book) {
        books.push_back(book);  
    }

    // รับคำสั่งทีละบรรทัดจน EOF
    while (std::getline(std::cin, input_line)) {
        if (input_line.empty()) {
            continue;
        }
        char command = input_line[0];

        if (command == 'M') {
            //เอาหนังสือบนกอง books ไปเข้าคิวอ่านของ miena
            if (!books.empty()) {
                miena_queue.push_back(books.back());
                books.pop_back();
            }
        } else if (command == 'm') {
            //เอาหนังสือคิวแรกของ miena ไปวางไว้บนกองหนังสือ book
            if (!miena_queue.empty()) {
                books.push_back(miena_queue.front());
                miena_queue.erase(miena_queue.begin());
            }
        } else if (command == 'L') {
            //เอาหนังสือบนกอง books ไปเข้าคิวอ่านของ luna
            if (!books.empty()) {
                luna_queue.push_back(books.back());
                books.pop_back();
            }
        } else if (command == 'l') {
            //เอาหนังสือคิวแรกของ luna ไปวางไว้บนกองหนังสือ book
            if (!luna_queue.empty()) {
                books.push_back(luna_queue.front());
                luna_queue.erase(luna_queue.begin());
            }
        } else if (command == 'P' || command == 'p') {
            // แสดง คิวการอ่าน และหนังสือบนกองที่เหลือ
            printStatus(books, miena_queue, luna_queue);
        }  else {
            std::cout << "Input Error" << std::endl;
            break;
        }
    }

    return 0;
}
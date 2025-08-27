#include <iostream>
#include <string>
#include <vector>


bool isPossible(std::vector<std::string> subStrings, std::string pattern, int startIndex) {
    if (startIndex == pattern.length()) {
        return true;
    }
    // วนลูปเพื่อลองใช้แต่ละป้ายห้อยคอ
    for (int i = 0; i < subStrings.size(); ++i) {
        std::string currentTag = subStrings[i];
        int tagLength = currentTag.length();

        // ตรวจสอบว่าป้ายนี้สามารถต่อที่ startIndex ได้หรือไม่
        if (startIndex + tagLength <= pattern.length()) {
            std::string sub = pattern.substr(startIndex, tagLength);
            
            if (sub == currentTag) {
                // ถ้าต่อได้ ให้เรียก recursive เพื่อลองต่อส่วนที่เหลือ
                if (isPossible(subStrings, pattern, startIndex + tagLength)) {
                    return true; // ถ้าสำเร็จก็คืนค่า true ทันที
                }
            }
        }
    }
    return false;
}

int main() {
    int n;
    std::vector<std::string> subStrings;
    std::string pattern;
    

    //----- INPUT -----//
    std::cin >> n;
    for(int i = 0; i < n; i++) {
        std::cin >> pattern;
        subStrings.push_back(pattern);
    }
    std::cin >> pattern;
    //-----------------//


    if (isPossible(subStrings, pattern, 0)) {
        std::cout << "POSSIBLE\n";
    } else {
        std::cout << "IMPOSSIBLE\n";
    }
    
    return 0;
}
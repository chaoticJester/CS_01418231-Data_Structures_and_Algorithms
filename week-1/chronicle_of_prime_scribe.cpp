#include <iostream>
#include <vector>
using namespace std;

int main() {
    //รับ input เลขที่ต้องการตรวจสอบ
    long long int input;
    cin >> input;
    
    //ตรวจว่าน้อยกว่า 2 หรือไม่
    if(input < 2) {
        cout << "ERROR!" << endl;
    } else {

        //สร้าง vector ที่เก็บค่าความจริงมาตามจำนวน input + 1 และเซ็ตค่าเริ่มต้นให้ทุกตัวเป็น true
        vector<bool> array(input + 1, true);
        array[0] = false;
        array[1] = false;

        //กำหนดค่าให้ทุก index ใน vector ที่หารได้ด้วยจำนวนเฉพาะเก็บค่า false ยกเว้นตัวมันเอง
        for(long long int i = 2; i * i <= input; i++) {
            if(array[i] == true) {
                for(long long int j = i * i; j <= input; j+= i) {
                    array[j] = false;
                }
            }

        }

        //ตรวจสอบว่าเป็นจำนวนเฉพาะหรือไม่
        if(array[input] == false) {
            cout << "Unrelated" << endl;
        } else {
            //บวกนับตำแหน่งของเลขจำนวนเฉพาะ
            int posi_input = 0;
            for(int i = 2; i <= input; i++) {
                if(array[i] == true) {
                    posi_input++;
                }
            }  
            
            //แสดงผลลัพธ์เป็นตำแหน่งของจำนวนเฉพาะ
            cout << posi_input;
            if (posi_input % 100 >= 11 && posi_input % 100 <= 13) {
                cout << "th" << endl;
            } else if (posi_input % 10 == 1) {
                cout << "st" << endl;
            } else if (posi_input % 10 == 2) {
                cout << "nd" << endl;
            } else if (posi_input % 10 == 3) {
                cout << "rd" << endl;
            } else {
                cout << "th" << endl;
            }
        }
    }
}
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    //รับ input j, K, d มา
    int expo;
    double require;
    int day;
    cin >> expo >> require;
    cin >> day;

    //คำนวนค่า P และกำหนดตัวแปรอื่นๆ
    double P = 1 * pow(10, expo);
    int food;
    double total_nutrient = 0;
    int milk = 0;
    int promax_milk = 0;

    //EPSILON
    const double EPS = 1e-9;

    //รับ input จำนวนเม็ดอาหารในแต่ละวัน
    for(int i = 0; i < day; i++) {
        cin >> food;

        //คำนวนสารอาหารแบบลุงและแบบโชค
        double N_uncle = food * P; 

        double N_chok = 0;
        for(int j = 0; j < food; j++) {
            N_chok += P;
        }

        //เช็คว่าผลิตนมสูตรปกติได้ไหม
        if( fabs(N_chok / require) > 1.00 || fabs(N_chok / require - 1.00) < EPS) {
            // cout << "M : " << fabs(N_chok / require) << " " << N_chok / require << endl;
            milk++;
            // cout << "milk : " << milk << endl;
        }
        //เช็คว่าผลิตนมสูตรโปรแมกส์ได้ไหม
        if(fabs((N_chok + N_uncle) - require) < EPS) {
            promax_milk++;
        }
        // printf("N_chok : %.17lf, N_uncle : %.17lf\n", N_chok, N_uncle);
        total_nutrient += N_chok;
    }

    //Output 
    cout << "Milk : " << milk << endl;
    cout << "ProMax Milk : " << promax_milk << endl;
    cout << fixed << setprecision(17) << "Nutrient : " << total_nutrient << endl;

    return 0;
}
#include <iostream>
#include <cmath>
using namespace std;

int promaxMilk(int f, double P, double K){
    double n = 2 * (f * P);
    if(n == K) {
        return 1;
    }
    return 0;
}

int normalMilk(int f, double P, double K){
    double n = (f * P);
    if(n >= K) {
        return 1;
    }
    return 0;
}

int main() {
    int j;
    double K;
    int day;
    
    cin >> j;
    cin >> K;
    cin >> day;
    
    long double P = pow(10.0L, j);
    
    int milk = 0;
    int promax_milk = 0;
    double cow_food;
    long double nutrients = 0;
    
    for(int i = 0; i < day; i++) {
        cin >> cow_food;
        nutrients += cow_food;
        if(normalMilk(cow_food, P, K)) {
            milk ++;
        }
        if(promaxMilk(cow_food, P, K)) {
            promax_milk ++;
        }
    }
    
    printf("Milk : %d\n", milk);
    printf("ProMax Milk : %d\n", promax_milk);
    printf("Nutrient : %17Lf", nutrients);
    
    return 0;
}
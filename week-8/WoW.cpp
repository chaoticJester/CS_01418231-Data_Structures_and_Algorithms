#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
using namespace std;

struct City {
    int number;
    int army;
    vector<City*> next_city;
};

void fullEngage(City* our_city, City* enemy_city, vector<int> &successInvade) {
    if(!enemy_city || our_city->army <= 0 ) return;
    
    if(our_city != enemy_city) {
        printf("#%d - %d, %d\n", enemy_city->number, our_city->army, enemy_city->army);
        
        int old_army = our_city->army;
        if(our_city->army >= enemy_city->army) {
            our_city->army = floor(old_army + (enemy_city->army * 0.7));
            printf("(+%d, %d)\n\n", our_city->army - old_army, our_city->army);
            successInvade.push_back(enemy_city->number);
        } else {
            our_city->army = floor(old_army - (old_army * 0.3));
            printf("(%d, %d)\n\n", our_city->army - old_army, our_city->army);
            return;
        }
    }
    
    if(enemy_city->next_city.size() > 0) {
        for(City* next_city : enemy_city->next_city) {
            fullEngage(our_city, next_city, successInvade);
        }
    }
}

int main() {
    int cityCount, our_army;
    cin >> cityCount >> our_army;
    
    vector<City*> allCity(cityCount);
    allCity[0] = new City{0, our_army, {}};
    
    for(int i = 1; i < cityCount; i++) {
        int city_number, prev_city, enemy_army;
        cin >> city_number >> prev_city >> enemy_army;
        allCity[city_number] = new City{city_number, enemy_army, {}};
        allCity[prev_city]->next_city.push_back(allCity[city_number]);
    }
    
    vector<int> successInvade;
    fullEngage(allCity[0], allCity[0], successInvade);

    cout << allCity[0]->army << "\n";
    if(!successInvade.empty()) {
        for(int num : successInvade) cout << num << " ";
        cout << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}

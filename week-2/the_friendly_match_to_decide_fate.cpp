#include <iostream>
#include <cmath>
using namespace std;

typedef struct {
    string name;
    int hp;
    int atk;
    int def;
    int maxenergy;
} Gundam;

int main() {
    //Input
    int gundam_amount;
    cin >> gundam_amount;

    int miena_use_powerup;
    double miena_atk_modifier;
    double miena_def_modifier;
    int miena_power_up_dura;

    int luna_use_powerup;
    double luna_atk_modifier;
    double luna_def_modifier;
    int luna_power_up_dura;

    Gundam miena_gundam[gundam_amount];
    Gundam luna_gundam[gundam_amount];

    string input_name;
    int input_hp;
    int input_atk;
    int input_def;
    int input_energy;

    cin >> miena_use_powerup >> miena_atk_modifier >> miena_def_modifier >> miena_power_up_dura;
    for(int i = 0; i < gundam_amount; i++) {
        cin >> input_name >> input_hp >> input_atk >> input_def >> input_energy;
        miena_gundam[i].name = input_name;
        miena_gundam[i].hp = input_hp;
        miena_gundam[i].atk = input_atk;
        miena_gundam[i].def = input_def;
        miena_gundam[i].maxenergy = input_energy;
    }

    cin >> luna_use_powerup >> luna_atk_modifier >> luna_def_modifier >> luna_power_up_dura;
    for(int i = 0; i < gundam_amount; i++) {
        cin >> input_name >> input_hp >> input_atk >> input_def >> input_energy;
        luna_gundam[i].name = input_name;
        luna_gundam[i].hp = input_hp;
        luna_gundam[i].atk = input_atk;
        luna_gundam[i].def = input_def;
        luna_gundam[i].maxenergy = input_energy;
    }

    //Battle begins
    int miena_energy = 0;
    int luna_energy = 0;
    int turn = 0;
    int miena_g_num = 0;
    int luna_g_num = 0;
    int miena_left_g = gundam_amount;
    int luna_left_g = gundam_amount;
    while(miena_left_g && luna_left_g) {
        
        int miena_atk = miena_gundam[miena_g_num].atk;
        int luna_atk = luna_gundam[luna_g_num].atk;
        int miena_def = miena_gundam[miena_g_num].def;
        int luna_def = luna_gundam[luna_g_num].def;
        int miena_dmg;
        int luna_dmg;
        
        // cout << "turn: " << turn << endl;
        if(turn % 2 == 0) {
            if(miena_use_powerup == miena_g_num && miena_power_up_dura > 0) {
                miena_atk = floor(miena_atk * miena_atk_modifier );
                miena_power_up_dura--;
            }
            if(miena_energy == miena_gundam[miena_g_num].maxenergy) {
                miena_atk *= 2;
            }
            if(luna_use_powerup == luna_g_num && luna_power_up_dura > 0) {
                luna_def = floor(luna_def * luna_def_modifier );
            }
            // cout << miena_atk << endl;
            miena_dmg = floor((miena_atk * miena_atk) / luna_def);
            luna_gundam[luna_g_num].hp -= miena_dmg;
            // cout << miena_gundam[miena_g_num].name << " attacked " << luna_gundam[luna_g_num].name << " and dealed " << miena_dmg << " dmg" << endl;
            if(luna_gundam[luna_g_num].hp <= 0) {
                luna_g_num++;
                luna_left_g--;
                luna_energy = 0;
            }
            // cout << miena_dmg << endl;
            if(miena_energy == miena_gundam[miena_g_num].maxenergy) {
                miena_energy = 0;
            } else {
                miena_energy++;
            }
        } else if (turn % 2 != 0) {
            if(luna_use_powerup == luna_g_num && luna_power_up_dura > 0) {
                luna_atk = floor(luna_atk * luna_atk_modifier );
                luna_power_up_dura--;
            }
            if(luna_energy == luna_gundam[luna_g_num].maxenergy) {
                luna_atk *= 2;
            }
            if(miena_use_powerup == miena_g_num && miena_power_up_dura > 0) {
                miena_def = floor(miena_def * miena_def_modifier );
            }
            // cout << luna_atk << endl;
            luna_dmg = floor(luna_atk * luna_atk / miena_def);
            miena_gundam[miena_g_num].hp -= luna_dmg;
            // cout << luna_gundam[luna_g_num].name << " attacked " << miena_gundam[miena_g_num].name << " and dealed " << luna_dmg << " dmg" << endl;
            if(miena_gundam[miena_g_num].hp <= 0) {
                miena_g_num++;
                miena_left_g --;
                miena_energy = 0;
            }
            // cout << luna_dmg << endl;
            if(luna_energy == luna_gundam[luna_g_num].maxenergy) {
                luna_energy = 0;
            } else {
                luna_energy++;
            }
        }

        // printf("M_en %d, L_en %d\n", miena_energy, luna_energy);
        turn ++;
        // cout << "-----------------------------------------------" << endl;
    }

    //Output
    if(miena_left_g > luna_left_g) {
        if(miena_left_g == 1) {
            printf("Miena is victorious with %d character left.\n", miena_left_g);
        } else {
            printf("Miena is victorious with %d characters left.\n", miena_left_g);
        }
    } else if (miena_left_g < luna_left_g) {
        if(luna_left_g == 1) {
            printf("Luna is victorious with %d character left.\n", luna_left_g);
        } else {
            printf("Luna is victorious with %d characters left.\n", luna_left_g);
        }
    }

    if(turn == 1) {
        printf("The battle took 1 turn.\n");
    } else {
        printf("The battle took %d turns.\n", turn);
    }

    return 0;
}
#include <iostream>
#include <cmath>
using namespace std;

typedef struct {
    string name;
    int hp;
    int atk;
    int def;
    int maxenergy;
} Gundam;

int main() {
    //Input
    int gundam_amount;
    cin >> gundam_amount;

    int miena_use_powerup;
    double miena_atk_modifier;
    double miena_def_modifier;
    int miena_power_up_dura;

    int luna_use_powerup;
    double luna_atk_modifier;
    double luna_def_modifier;
    int luna_power_up_dura;

    Gundam miena_gundam[gundam_amount];
    Gundam luna_gundam[gundam_amount];

    string input_name;
    int input_hp;
    int input_atk;
    int input_def;
    int input_energy;

    cin >> miena_use_powerup >> miena_atk_modifier >> miena_def_modifier >> miena_power_up_dura;
    for(int i = 0; i < gundam_amount; i++) {
        cin >> input_name >> input_hp >> input_atk >> input_def >> input_energy;
        miena_gundam[i].name = input_name;
        miena_gundam[i].hp = input_hp;
        miena_gundam[i].atk = input_atk;
        miena_gundam[i].def = input_def;
        miena_gundam[i].maxenergy = input_energy;
    }

    cin >> luna_use_powerup >> luna_atk_modifier >> luna_def_modifier >> luna_power_up_dura;
    for(int i = 0; i < gundam_amount; i++) {
        cin >> input_name >> input_hp >> input_atk >> input_def >> input_energy;
        luna_gundam[i].name = input_name;
        luna_gundam[i].hp = input_hp;
        luna_gundam[i].atk = input_atk;
        luna_gundam[i].def = input_def;
        luna_gundam[i].maxenergy = input_energy;
    }

    //Battle begins
    int miena_energy = 0;
    int luna_energy = 0;
    int turn = 0;
    int miena_g_num = 0;
    int luna_g_num = 0;
    int miena_left_g = gundam_amount;
    int luna_left_g = gundam_amount;
    while(miena_left_g && luna_left_g) {
        
        int miena_atk = miena_gundam[miena_g_num].atk;
        int luna_atk = luna_gundam[luna_g_num].atk;
        int miena_def = miena_gundam[miena_g_num].def;
        int luna_def = luna_gundam[luna_g_num].def;
        int miena_dmg;
        int luna_dmg;
        
        // cout << "turn: " << turn << endl;
        if(turn % 2 == 0) {
            if(miena_use_powerup == miena_g_num && miena_power_up_dura > 0) {
                miena_atk = floor(miena_atk * miena_atk_modifier );
                miena_power_up_dura--;
            }
            if(miena_energy == miena_gundam[miena_g_num].maxenergy) {
                miena_atk *= 2;
            }
            if(luna_use_powerup == luna_g_num && luna_power_up_dura > 0) {
                luna_def = floor(luna_def * luna_def_modifier );
            }
            // cout << miena_atk << endl;
            miena_dmg = floor((miena_atk * miena_atk) / luna_def);
            luna_gundam[luna_g_num].hp -= miena_dmg;
            // cout << miena_gundam[miena_g_num].name << " attacked " << luna_gundam[luna_g_num].name << " and dealed " << miena_dmg << " dmg" << endl;
            if(luna_gundam[luna_g_num].hp <= 0) {
                luna_g_num++;
                luna_left_g--;
                luna_energy = 0;
            }
            // cout << miena_dmg << endl;
            if(miena_energy == miena_gundam[miena_g_num].maxenergy) {
                miena_energy = 0;
            } else {
                miena_energy++;
            }
        } else if (turn % 2 != 0) {
            if(luna_use_powerup == luna_g_num && luna_power_up_dura > 0) {
                luna_atk = floor(luna_atk * luna_atk_modifier );
                luna_power_up_dura--;
            }
            if(luna_energy == luna_gundam[luna_g_num].maxenergy) {
                luna_atk *= 2;
            }
            if(miena_use_powerup == miena_g_num && miena_power_up_dura > 0) {
                miena_def = floor(miena_def * miena_def_modifier );
            }
            // cout << luna_atk << endl;
            luna_dmg = floor(luna_atk * luna_atk / miena_def);
            miena_gundam[miena_g_num].hp -= luna_dmg;
            // cout << luna_gundam[luna_g_num].name << " attacked " << miena_gundam[miena_g_num].name << " and dealed " << luna_dmg << " dmg" << endl;
            if(miena_gundam[miena_g_num].hp <= 0) {
                miena_g_num++;
                miena_left_g --;
                miena_energy = 0;
            }
            // cout << luna_dmg << endl;
            if(luna_energy == luna_gundam[luna_g_num].maxenergy) {
                luna_energy = 0;
            } else {
                luna_energy++;
            }
        }

        // printf("M_en %d, L_en %d\n", miena_energy, luna_energy);
        turn ++;
        // cout << "-----------------------------------------------" << endl;
    }

    //Output
    if(miena_left_g > luna_left_g) {
        if(miena_left_g == 1) {
            printf("Miena is victorious with %d character left.\n", miena_left_g);
        } else {
            printf("Miena is victorious with %d characters left.\n", miena_left_g);
        }
    } else if (miena_left_g < luna_left_g) {
        if(luna_left_g == 1) {
            printf("Luna is victorious with %d character left.\n", luna_left_g);
        } else {
            printf("Luna is victorious with %d characters left.\n", luna_left_g);
        }
    }

    if(turn == 1) {
        printf("The battle took 1 turn.\n");
    } else {
        printf("The battle took %d turns.\n", turn);
    }

    return 0;
}

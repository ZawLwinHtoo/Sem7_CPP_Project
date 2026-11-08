//
// Created by zl_shit_h on 03/08/23.
//
#include "main.h"
using namespace std;



int main(){
    load_data_from_file();
    cout << "Loaded " << user << " local player profiles.\n";
    welcome();
    return 0;
}

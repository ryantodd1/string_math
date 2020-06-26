#include <iostream>
#include "nstr.h"
#include <windows.h>

// Allows user to calculate eulars number to large 
//  decimal precision
//
// It is kind of a guessing game for the needed precision
// One will realize soon it needs to be large to account for dividing by factorials


nstr fact(int);

int main() {

    nstr::set_precision(60);
    nstr::set_disp_precision(54);

    nstr e = "0";
    for (int i = 0; i < 50; i++) {
        e = e + "1" / fact(i);
        std::cout << "e ~ " << e << "\n";
        Sleep(500);
    }

    std::cout << "Press enter to exit...\n";
    std::cin.get();
    return 0;
}

nstr fact(int n) {
    nstr prod = "1";

    for (int i = 2; i <= n; i++) {
        prod = prod * std::to_string(i);
    }
    return prod;
}

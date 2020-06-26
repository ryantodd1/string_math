#include <iostream>
#include "nstr.h"

// Showing basic examples of calculations

int main() {

    nstr::set_precision(30);
    nstr::set_disp_precision(20);

    nstr num0 = "7777";
    nstr num1 = "-23.5678";
    

    std::cout << num0 << " + " << num1 << " = " << num0 + num1 << "\n";
    std::cout << num0 << " - " << num1 << " = " << num0 - num1 << "\n";
    std::cout << num0 << " * " << num1 << " = " << num0 * num1 << "\n";
    std::cout << num0 << " / " << num1 << " = " << num0 / num1 << "\n";

    std::cout << num0 << " + " << "0.23" << " = " << num0 + "0.23" << "\n";
    std::cout << num0 << " - " << "0.23" << " = " << num0 - "0.23" << "\n";
    std::cout << num0 << " * " << "0.23" << " = " << num0 * "0.23" << "\n";
    std::cout << num0 << " / " << "0.23" << " = " << num0 / "0.23" << "\n";

    std::cout << "1.2356" << " + " << num1 << " = " << "1.2356" + num1 << "\n";
    std::cout << "1.2356" << " - " << num1 << " = " << "1.2356" - num1 << "\n";
    std::cout << "1.2356" << " * " << num1 << " = " << "1.2356" * num1 << "\n";
    std::cout << "1.2356" << " / " << num1 << " = " << "1.2356" / num1 << "\n";

    return 0;
}

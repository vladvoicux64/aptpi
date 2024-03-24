#include "Package.h"
#include "Installation.h"
#include <ctime>
#include <iostream>


int main() {
    time_t now = time(nullptr);
    tm ltm = *localtime(&now);

    Package pckg1("dependency", AUTOMATIC), pckg2("dependency", MANUAL);
    Installation install(ltm, pckg1, {pckg2});
    std::cout << install;
    std::cout << pckg2.get_name();
    return 0;
}

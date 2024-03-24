#include "Package.h"
#include "Installation.h"
#include <ctime>
#include <iostream>


int main() {
    Package pckg1("master", AUTOMATIC), pckg2("dependency", MANUAL);
    Installation install({pckg1}, {pckg2});
    std::cout << install;
    std::cout << pckg2.get_name() << std::endl;
    std::cout << install.get_package_count();
    return 0;
}

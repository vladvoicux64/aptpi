#include "Package.h"

int main() {
    Package pckg1("dependency", AUTOMATIC), pckg2("dependency", MANUAL);
    pckg1.print_information();
    return 0;
}

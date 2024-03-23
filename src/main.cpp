#include <ctime>
#include "Package.h"

int main() {
    time_t now = time(nullptr);
    tm ltm = *localtime(&now);

    Package dep("dependency", ltm, AUTOMATIC, {}, {});
    Package parent("parent", ltm, MANUAL, {}, {&dep});

    dep.add_parent_package(&parent);
    parent.print_information();
    return 0;
}

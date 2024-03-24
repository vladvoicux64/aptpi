#include "Session.h"
#include <iostream>


int main() {
    Session sesh("../history.log.txt");
    Session sesh2(sesh);
    sesh2.scan_history();
    Session sesh3 = sesh;
    std::cout << sesh3;
    sesh3 = sesh2;

    sesh3.display_installations_info(1);
    return 0;
}

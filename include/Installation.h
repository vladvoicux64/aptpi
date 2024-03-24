//
// Created by vladvoicux64 on 3/23/24.
//

#ifndef APTPD_INSTALLATION_H
#define APTPD_INSTALLATION_H


#include <vector>
#include <ctime>
#include <ostream>
#include "Package.h"


class Installation {
    std::vector<Package> masters_;
    std::vector<Package> dependencies_;
    tm installation_date_;
public:
    Installation(const tm &installation_date, const std::vector<Package> &masters = {{"___NULLPCKG___", AUTOMATIC}},
                 const std::vector<Package> &dependencies = {});

    Installation(const std::vector<Package> &masters = {{"___NULLPCKG___", AUTOMATIC}},
                 const std::vector<Package> &dependencies = {});

    [[maybe_unused]] void set_installation_date(const tm &installation_date);

    [[maybe_unused]] void add_master(const Package &master);

    [[maybe_unused]] void add_dependency(const Package &dependency);
    std::size_t get_package_count();
    friend std::ostream &operator<<(std::ostream &ostream, const Installation &installation);
};


#endif //APTPD_INSTALLATION_H

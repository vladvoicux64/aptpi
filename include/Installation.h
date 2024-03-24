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
    Package master_;
    std::vector<Package> dependencies_;
    tm installation_date_;
public:
    Installation(const tm &installation_date, Package master = {"___NULLPCKG___", AUTOMATIC},
                 const std::vector<Package> &dependencies = {});

    Installation(Package master = {"___NULLPCKG___", AUTOMATIC}, const std::vector<Package> &dependencies = {});

    void set_installation_date(const tm &installation_date);

    void set_dependencies(const std::vector<Package> &dependencies);
    std::size_t get_package_count();
    friend std::ostream &operator<<(std::ostream &ostream, const Installation &installation);
};


#endif //APTPD_INSTALLATION_H

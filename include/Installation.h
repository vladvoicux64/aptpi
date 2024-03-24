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
    Installation(const tm &installation_date, Package master, const std::vector<Package> &dependencies = {});

    friend std::ostream &operator<<(std::ostream &ostream, const Installation &installation);
};


#endif //APTPD_INSTALLATION_H

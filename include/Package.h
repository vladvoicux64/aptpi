//
// Created by vladvoicux64 on 3/20/24.
//

#ifndef APTPD_PACKAGE_H
#define APTPD_PACKAGE_H


#include "string"
#include "vector"


typedef enum package_installation_mode {
    AUTOMATIC,
    MANUAL
} package_installation_mode;


class Package {
    std::string name_;
    package_installation_mode installation_mode_;
public:
    Package(std::string name, const package_installation_mode &installation_mode);

    std::string get_name() const;
    friend std::ostream & operator<<(std::ostream &ostream, const Package &package);
};


#endif //APTPD_PACKAGE_H

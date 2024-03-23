//
// Created by vladvoicux64 on 3/20/24.
//

#ifndef APTPD_PACKAGE_H
#define APTPD_PACKAGE_H


#include "string"
#include "ctime"
#include "vector"


typedef enum package_installation_mode {
    AUTOMATIC,
    MANUAL
} package_installation_mode;


class Package {
protected:
    std::string name_;
    tm installation_date_;
    package_installation_mode installation_mode_;
    std::vector<Package *> parent_packages_;
    std::vector<Package *> dependencies_;
public:
    Package(std::string name, const tm &installation_date, const package_installation_mode &installation_mode,
            const std::vector<Package *> &parent_packages, const std::vector<Package *> &dependencies);

    void add_parent_package(Package *parent);
    void print_information() const;
    friend std::ostream & operator<<(std::ostream &ostream, const Package &package);
};


#endif //APTPD_PACKAGE_H

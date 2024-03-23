//
// Created by vladvoicux64 on 3/20/24.
//

#include "Package.h"
#include <utility>
#include <ostream>
#include <ctime>
#include <iostream>


Package::Package(std::string name, const tm &installation_date, const package_installation_mode &installation_mode,
                 const std::vector<Package *> &parent_packages,
                 const std::vector<Package *> &dependencies) : name_(std::move(name)),
                                                               installation_date_(installation_date),
                                                               installation_mode_(installation_mode),
                                                               parent_packages_(parent_packages),
                                                               dependencies_(dependencies)
{}

// ^^^ De ce nu am folosit const & la name: varianta utilizata de mine elimina total copy-urile atunci cand name este un rvalue, comparat cu un copy daca as fi folosit const &.
// Un thread de Stack Overflow relevant: https://stackoverflow.com/questions/51705967/advantages-of-pass-by-value-and-stdmove-over-pass-by-reference/51706522

void Package::add_parent_package(Package *const parent)
{
    this->parent_packages_.emplace_back(parent);
}

void Package::print_information() const
{
    std::cout << *this;
}

std::ostream & operator<<(std::ostream &ostream, const Package &package)
{
    char installation_date_string[128];
    strftime(installation_date_string, sizeof installation_date_string, "%c\n", &package.installation_date_);
    ostream << "Package name: " << package.name_ << std::endl;
    ostream << "Installed at: " << installation_date_string;
    ostream << "Installation mode: " << (package.installation_mode_ ? "automatic" : "manual") << std::endl;
    ostream << "Dependencies: " << std::endl;
    if(!package.dependencies_.empty())
    {
        for (const auto& dependency : package.dependencies_)
        {
            ostream << "\t" << dependency->name_ << ' ';
        }
    }
    else ostream << "\tTh. package has no dependencies.";
    return ostream;
}

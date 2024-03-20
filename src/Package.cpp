//
// Created by vladvoicux64 on 3/20/24.
//

#include "Package.h"
#include <utility>


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

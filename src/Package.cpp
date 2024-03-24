//
// Created by vladvoicux64 on 3/20/24.
//

#include "Package.h"
#include <utility>
#include <ostream>
#include <iostream>


Package::Package(std::string name, const package_installation_mode &installation_mode) :
        name_(std::move(name)),
        installation_mode_(installation_mode)
{}

// ^^^ De ce nu am folosit const & la name: varianta utilizata de mine elimina total copy-urile atunci cand name este un rvalue, comparat cu un copy daca as fi folosit const &.
// Un thread de Stack Overflow relevant: https://stackoverflow.com/questions/51705967/advantages-of-pass-by-value-and-stdmove-over-pass-by-reference/51706522

std::string Package::get_name() const
{
    return this->name_;
}

std::ostream & operator<<(std::ostream &ostream, const Package &package)
{
    ostream << "Package name: " << package.name_ << std::endl;
    ostream << "Installation mode: " << (package.installation_mode_ ? "automatic" : "manual") << std::endl;
    return ostream;
}

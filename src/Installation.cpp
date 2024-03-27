//
// Created by vladvoicux64 on 3/23/24.
//

#include <ctime>
#include <string>
#include <sstream>
#include "Installation.h"


Installation::Installation(const tm &installation_date, const std::vector<Package> &masters,
                           const std::vector<Package> &dependencies)
        : masters_(masters),
          dependencies_(dependencies), installation_date_(installation_date)
{}

Installation::Installation(const std::vector<Package> &masters,
                           const std::vector<Package> &dependencies)
        : masters_(masters),
          dependencies_(dependencies), installation_date_()
{
    time_t now = time(nullptr);
    this->installation_date_ = *localtime(&now);
}

std::size_t Installation::get_package_count() const
{
    return 1 + this->dependencies_.size();
}

std::ostream &operator<<(std::ostream &ostream, const Installation &installation)
{
    char date_buffer[128];
    strftime(date_buffer, 128, "%c\n", &installation.installation_date_);

    ostream << "Installation date: " << date_buffer;
    ostream << "\nPackages installed:\n\n";
    for (const auto &master: installation.masters_) {
        ostream << master;
    }
    if (!installation.dependencies_.empty()) {
        ostream << "\nDependencies installed:\n\n";
        for (const auto &dependency: installation.dependencies_) {
            ostream << dependency;
        }
    } else {
        ostream << "This package did not install any dependencies.\n";
    }
    return ostream;
}

void Installation::set_installation_date(const tm &installation_date)
{
    this->installation_date_ = installation_date;
}

void Installation::add_master(const Package &master)
{
    if (this->masters_.at(0).get_name() == "___NULLPCKG___") this->masters_.clear();
    this->masters_.emplace_back(master);
}

void Installation::add_dependency(const Package &dependency)
{
    this->dependencies_.emplace_back(dependency);
}

std::string Installation::get_package_names() const
{
    std::stringstream sstream{};
    for (const auto &master : this->masters_)
    {
        sstream << master.get_name() << ' ';
    }
    for (const auto &dependency : this->dependencies_)
    {
        sstream << dependency.get_name() << ' ';
    }
    std::string rv{sstream.str()};
    rv.pop_back();
    return rv;
}

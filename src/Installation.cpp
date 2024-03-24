//
// Created by vladvoicux64 on 3/23/24.
//

#include <utility>
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

std::size_t Installation::get_package_count()
{
    return 1 + this->dependencies_.size();
}

std::ostream &operator<<(std::ostream &ostream, const Installation &installation)
{
    char date_buffer[128];
    strftime(date_buffer, 128, "%c\n", &installation.installation_date_);

    ostream << "Installation date: " << date_buffer;
    ostream << "Packages installed:\n\n";
    for (const auto &master: installation.masters_) {
        ostream << master << std::endl;
    }
    if (!installation.dependencies_.empty()) {
        ostream << "\nDependencies installed:\n\n";
        for (const auto &dependency: installation.dependencies_) {
            ostream << dependency << std::endl;
        }
    } else {
        ostream << "\nThis package did not install any dependencies.\n";
    }
    return ostream;
}

void Installation::set_installation_date(const tm &installation_date)
{
    this->installation_date_ = installation_date;
}

void Installation::add_master(const Package &master)
{
    if (this->masters_[0].get_name() == "___NULLPCKG___") this->masters_.clear();
    this->masters_.emplace_back(master);
}

void Installation::add_dependency(const Package &dependency)
{
    this->dependencies_.emplace_back(dependency);
}

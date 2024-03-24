//
// Created by vladvoicux64 on 3/23/24.
//

#include <utility>
#include "Installation.h"


Installation::Installation(const tm &installation_date, Package master, const std::vector<Package> &dependencies)
        : master_(std::move(master)),
          dependencies_(dependencies), installation_date_(installation_date)
{}

Installation::Installation(Package master, const std::vector<Package> &dependencies)
        : master_(std::move(master)),
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
    ostream << "Package installed:\n\n" << installation.master_;
    if (!installation.dependencies_.empty()) {
        ostream << "\n\nDependencies installed:\n\n";
        for (const auto &dependency: installation.dependencies_) {
            ostream << dependency << std::endl;
        }
    } else {
        ostream << "\n\nThis package did not install any dependencies.";
    }
    return ostream;
}

void Installation::set_installation_date(const tm &installation_date)
{
    this->installation_date_ = installation_date;
}

void Installation::set_master_package(const Package &master)
{
    this->master_ = master;
}

void Installation::add_dependency(const Package &dependency)
{
    this->dependencies_.emplace_back(dependency);
}

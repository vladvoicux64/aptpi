//
// Created by vladvoicux64 on 3/24/24.
//

#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Session.h"
#include "Package.h"

std::vector<std::string> split_str(const std::string &s, const std::string &delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}


Session::Session(const std::string &history_file_path) : history_file_(history_file_path), file_path_(history_file_path)
{}

void Session::scan_history()
{
    std::string line;
    std::vector<std::string> buff;


    while (std::getline(this->history_file_, line)) {
        if (!line.empty()) buff.emplace_back(line);
        if (line.starts_with("End-Date")) {
            if (buff.size() >= 5 && buff.at(1).find(" install ") != std::string::npos) {
                tm start_date = {};
                buff.at(0).erase(0, 12);
                std::stringstream time_line_ss(buff.at(0));
                time_line_ss >> std::get_time(&start_date, "%F  %T");

                Installation in_progress(start_date);

                line = buff.at(3);
                line.erase(0, 9);
                buff.clear();
                buff = split_str(line, "),");

                for (const auto &pckg: buff) {
                    size_t name_end = pckg.find(':');
                    std::string pckg_name = pckg.substr(0, name_end);
                    pckg_name.erase(0,pckg_name.find_first_not_of(" \n\r\t"));
                    package_installation_mode pckg_inst_mode = ((pckg.find(", automatic") != std::string::npos)
                                                                ? AUTOMATIC : MANUAL);
                    if (pckg_inst_mode == MANUAL) {
                        in_progress.add_master({pckg_name, pckg_inst_mode});
                    } else in_progress.add_dependency({pckg_name, pckg_inst_mode});
                }

                this->installations_.emplace_back(in_progress);
            }
            buff.clear();
        }
    }
}

Session::~Session()
{
    this->history_file_.close();
}

std::ostream &operator<<(std::ostream &ostream, const Session &session)
{
    ostream << "This session has found " << session.installations_.size()
            << " installations in the log file provided.\n";
    ostream << "The logfile is at: " << session.file_path_ << std::endl;
    ostream
            << "To display more information, use the .dispaly_installations_info(1) method, specifying an index out of the "
            << session.installations_.size() << " installations. ";
    ostream << "Do not specify an index to display all the installations. ";
    ostream << "The information will be displayed to your console.";
    return ostream;
}

std::string Session::display_installations_info(size_t index) const
{
    std::stringstream sstream{};
    size_t inst_count = this->installations_.size();
    if (index == (size_t) -1) {
        sstream << "Displaying " << inst_count << " installations:\n\n";
        for (const auto &installation: this->installations_) {
            sstream << installation << std::endl;
        }
    } else if ((index < inst_count)) {
        sstream << "Displaying the installation number " << index << ":\n\n";
        sstream << this->installations_.at(index) << std::endl;
    } else sstream << "Invalid index.";
    return sstream.str();
}

Session::Session(Session &other) : history_file_(other.file_path_), file_path_(other.file_path_),
                                   installations_(other.installations_)
{}

Session &Session::operator=(const Session &other)
{
    this->history_file_.close();
    this->history_file_.open(other.file_path_);
    this->file_path_ = other.file_path_;
    this->installations_ = other.installations_;
    return *this;
}

std::string Session::generate_uninstall_command(size_t index) const
{
    //TODO exception catching
    std::stringstream sstream{};
    if(index < this->installations_.size())
    {
        sstream << "Use the following command to uninstall installation " << index << ":\n";
        sstream << "NOTE: You may break other packages that depend on the packages in the following command. Use with caution.\n";
        sstream << "sudo apt autoremove --purge " << this->installations_.at(index).get_package_names() << std::endl;
    }
    else sstream << "Failed attempt at generating uninstall command at index " << index << ": invalid index.\n";

    return sstream.str();
}

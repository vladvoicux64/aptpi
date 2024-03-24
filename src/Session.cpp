//
// Created by vladvoicux64 on 3/24/24.
//

#include <string>
#include <ctime>
#include <sstream>
#include <iostream>
#include "Session.h"
#include "Package.h"

std::vector<std::string> split_str(std::string s, std::string delimiter)
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
        if (line != "") buff.emplace_back(line);
        if (line.starts_with("End-Date")) {
            if (buff.size() >= 5 && buff[1].find(" install ") != buff[1].npos) {
                tm start_date = {};
                buff[0].erase(0, 12);
                std::stringstream time_line_ss(buff[0]);
                time_line_ss >> std::get_time(&start_date, "%F  %T");

                Installation in_progress(start_date);

                line = buff[3];
                line.erase(0, 9);
                buff.clear();
                buff = split_str(line, "),");

                for (auto pckg: buff) {
                    size_t name_end = pckg.find(':');
                    std::string pckg_name = pckg.substr(0, name_end);
                    package_installation_mode pckg_inst_mode = ((pckg.find(", automatic") != pckg.npos) ? AUTOMATIC
                                                                                                        : MANUAL);
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
            << session.installations_.size() << " installations.";
    ostream << "Do not specify an index to display all the installations.";
    ostream << "The information will be displayed to your console.";
    return ostream;
}

void Session::display_installations_info(size_t index)
{
    size_t inst_count = this->installations_.size();
    if (index == (size_t) -1) {
        std::cout << "Displaying " << inst_count << " installations:\n\n";
        for (const auto &installation: this->installations_) {
            std::cout << installation << std::endl;
        }
        return;
    } else if ((index < inst_count)) {
        std::cout << "Displaying the installation number " << index << ":\n\n";
        std::cout << this->installations_[index];
    } else std::cout << "Invalid index.";
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

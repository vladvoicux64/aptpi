//
// Created by vladvoicux64 on 3/24/24.
//

#ifndef APTPD_SESSION_H
#define APTPD_SESSION_H


#include <vector>
#include <fstream>
#include <string>
#include <ostream>
#include "Installation.h"

class Session {
    std::ifstream history_file_;
    std::string file_path_;
    std::vector<Installation> installations_;
public:
    Session(const std::string &history_file_path);

    Session(Session &other);

    Session &operator=(const Session &other);

    ~Session();

    void scan_history();

    [[maybe_unused]] void display_installations_info(size_t index = -1);

    friend std::ostream &operator<<(std::ostream &ostream, const Session &session);
};

#endif //APTPD_SESSION_H

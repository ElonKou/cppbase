/*================================================================
*  Copyright (C)2021 All rights reserved.
*  FileName : cpptools.cc
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Sun 11 Sep 2022 02:32:18 PM CST
================================================================*/

#include "cpptools.hh"

namespace cpptools {

// print
std::vector<std::string> COLORS = {BLACK, BROWN, GREEN, RED, RED, GREEN, BLUE, BLACK, BROWN, YELLOW, PURPLE, CYAN, GRAY, WHITE};

void PrintInfo(std::string str, INFO_TYPE info_type) {
    std::string s = COLORS[size_t(info_type)] + str + NONE;
    printf("%s", s.c_str());
}

// File tools

std::vector<std::string> GetFiles(std::string dir) {
    std::vector<std::string> files;
    DIR*                     dp = opendir(dir.c_str());
    struct dirent*           dirp;
    while ((dirp = readdir(dp)) != NULL) {
        if (std::string(dirp->d_name) == "." || std::string(dirp->d_name) == "..") {
            continue;
        }
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);
    return files;
}

std::vector<std::string> Split(const std::string& s, const std::string& seperator) {
    std::vector<std::string> result;
    size_t                   i = 0;

    while (i != s.size()) {
        int flag = 0;
        while (i != s.size() && flag == 0) {
            flag = 1;
            for (size_t x = 0; x < seperator.size(); ++x)
                if (s[i] == seperator[x]) {
                    ++i;
                    flag = 0;
                    break;
                }
        }
        flag     = 0;
        size_t j = i;
        while (j != s.size() && flag == 0) {
            for (size_t x = 0; x < seperator.size(); ++x)
                if (s[j] == seperator[x]) {
                    flag = 1;
                    break;
                }
            if (flag == 0)
                ++j;
        }
        if (i != j) {
            result.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return result;
}

std::string& Replace_all(std::string& str, const std::string& old_value, const std::string& new_value) {
    while (true) {
        std::string::size_type pos(0);
        if ((pos = str.find(old_value)) != std::string::npos)
            str.replace(pos, old_value.length(), new_value);
        else
            break;
    }
    return str;
}

// Timer
Timer::Timer() {
    st   = std::chrono::high_resolution_clock::now();
    last = st;
    now  = st;
}

Timer::~Timer() {}

void Timer::Start() {
    now  = std::chrono::high_resolution_clock::now();
    last = now;
}

double Timer::StopMS() {
    now         = std::chrono::high_resolution_clock::now();
    double dura = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
    last        = now;
    return dura;
}

double Timer::StopUS() {
    now         = std::chrono::high_resolution_clock::now();
    double dura = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();
    last        = now;
    return dura;
}

inline double GetTimerMS(time_point t1, time_point t2) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

inline double GetTimerUS(time_point t1, time_point t2) {
    return std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
}

} // namespace cpptools
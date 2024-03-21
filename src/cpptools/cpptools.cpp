/*================================================================
*  Copyright (C)2021 All rights reserved.
*  FileName : cpptools.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sun 11 Sep 2022 02:32:18 PM CST
================================================================*/

#include "cpptools.hh"

namespace cpptools {

// print
std::vector<std::string> COLORS = {BLACK, BROWN, GREEN, RED, RED, GREEN, BLUE, BLACK, BROWN, YELLOW, PURPLE, CYAN, GRAY, WHITE};

void PrintInfo(std::string str, INFO_TYPE info_type) {
    std::string s = COLORS[size_t(info_type)] + str + NONEC;
    printf("%s", s.c_str());
}

// File tools

// example : "/home/biulab/app/TENCENT_EXP/qikan_cache/joint.json"
std::vector<std::string> GetFilePath(std::string path) {
    size_t      ipos_root = path.find_last_of('/');
    size_t      ipos_sub  = path.find_last_of('.');
    std::string path_root = path.substr(0, ipos_root);                                 // folder     : "/home/biulab/app/TENCENT_EXP/qikan_cache"
    std::string path_pat  = path.substr(ipos_root + 1, path.length() - ipos_root - 1); // file_path  : "joint.json"
    std::string path_name = path.substr(ipos_root + 1, ipos_sub - ipos_root - 1);      // short name : "joint"
    std::string path_sub  = path.substr(ipos_sub, path.length() - ipos_sub);           // sub name   : ".json"
    return {path_root, path_pat, path_name, path_sub};
}

std::vector<std::string> GetFiles(std::string dir, std::string pattern) {
    std::vector<std::string> files;
    DIR*                     dp = opendir(dir.c_str());
    struct dirent*           dirp;
    while ((dirp = readdir(dp)) != NULL) {
        if (std::string(dirp->d_name) == "." || std::string(dirp->d_name) == "..") {
            continue;
        }
        bool        ret = true;
        std::string tmp = std::string(dirp->d_name);
        if (pattern.size() > 0) {
            if (tmp.size() < pattern.size()) {
                continue;
            }
            for (size_t i = 0; i < pattern.size(); i++) {
                size_t idx = pattern.size() - 1 - i;
                size_t idy = tmp.size() - 1 - i;
                if (tmp[idy] != pattern[idx]) {
                    ret = false;
                    break;
                }
            }
            if (!ret) {
                continue;
            }
        }
        files.push_back(tmp);
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
            str.replace(pos, new_value.length(), new_value);
        else
            break;
    }
    return str;
}

std::string CombinePath(std::vector<std::string> paths) {
    std::string ret = "";
    for (size_t i = 0; i < paths.size(); i++) {
        if (i != 0) {
            if (paths[i][0] == '/') {
                paths[i] = paths[i].substr(1, paths[i].size() - 1);
            }
        }
        if (paths[i][paths[i].size() - 1] == '/') {
            paths[i] = paths[i].substr(0, paths[i].size() - 1);
        }
        if (i == 0) {
            ret = paths[i];
        } else {
            ret = ret + "/" + paths[i];
        }
    }
    return ret;
}

bool IsExist(std::string filename) {
    int ret = access(filename.c_str(), 0);
    return ret == 0;
}
bool CreateFodler(std::string foldername) {
    if (!IsExist(foldername)) {
        std::string cmd = "mkdir -p " + foldername;
        int         ret = system(cmd.c_str());
        return ret == 0;
    } else {
        return true;
    }
}

bool DeleteFolder(std::string foldername) {
    if (IsExist(foldername)) {
        std::string cmd = "rm -rf " + foldername;
        int         ret = system(cmd.c_str());
        return ret == 0;
    } else {
        std::cout << foldername << " doesn't exist." << std::endl;
        return true;
    }
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
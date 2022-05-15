#pragma once
#ifndef CPPTOOLS_HPP_
#define CPPTOOLS_HPP_

#define ABS(x) (x > 0 ? x : -x)
#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

#define NONE "\e[0m"
#define BLACK "\e[0;30m"
#define L_BLACK "\e[1;30m"
#define RED "\e[0;31m"
#define L_RED "\e[1;31m"
#define GREEN "\e[0;32m"
#define L_GREEN "\e[1;32m"
#define BROWN "\e[0;33m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[0;34m"
#define L_BLUE "\e[1;34m"
#define PURPLE "\e[0;35m"
#define L_PURPLE "\e[1;35m"
#define CYAN "\e[0;36m"
#define L_CYAN "\e[1;36m"
#define GRAY "\e[0;37m"
#define WHITE "\e[1;37m"

#define BOLD "\e[1m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m"
#define REVERSE "\e[7m"
#define HIDE "\e[8m"
#define CLEAR "\e[2J"
#define CLRLINE "\r\e[K"
#define CLOSE "\033[0m"

#include <dirent.h>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <typeinfo>
#include <unistd.h>
#include <vector>

// Random part
#define Random(x) (rand() % x)

namespace cpptools {

template<typename T>
inline void SetRandomSeed(unsigned int seed) {
    srand(seed);
}

template<typename T>
inline void SetRandomSeed() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
}

template<typename T>
inline bool RandomBool() {
    if (Random(2) == 1) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
inline int RandomInt(int range) {
    return Random(range);
}

template<typename T>
inline float RandomFloat() {
    return RandomInt<int>(1000000) * 1.0 / 1000000;
}

// convert types
template <class Type>
Type StringToNum(const std::string& str) {
    std::istringstream iss(str);
    Type               num;
    iss >> num;
    return num;
}

template <class Type>
std::string ToString(const Type& str) {
    std::istringstream iss(str);
    std::string        ret;
    iss >> ret;
    return ret;
}

// print color strings
enum INFO_TYPE {
    OK,      // BLACK
    WARNING, // BROWN
    SUCCEED, // GREEN
    ERROR,   // RED
    COLOR_RED,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_BLACK,
    COLOR_BROWN,
    COLOR_YELLOW,
    COLOR_PURPLE,
    COLOR_CYAN,
    COLOR_GRAY,
    COLOR_WHITE
};

const static std::vector<std::string> COLORS = {BLACK, BROWN, GREEN, RED, RED, GREEN, BLUE, BLACK, BROWN, YELLOW, PURPLE, CYAN, GRAY, WHITE};

template <typename T>
void PrintInfo(T str, INFO_TYPE info_type) {
    std::string s = COLORS[size_t(info_type)] + str + NONE;
    printf("%s", s.c_str());
}

// File tools

template<typename T>
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

template<typename T>
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

template<typename T>
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

}; // namespace cpptools

#endif
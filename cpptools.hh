/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : cpptools.hh
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Version  : 0.1
*  Date     : Sun 08 Jan 2023 03:03:54 PM CST
================================================================*/

#pragma once
#ifndef CPPTOOLS_HH
#define CPPTOOLS_HH

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

#include <chrono>
#include <dirent.h>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <typeinfo>
#include <unistd.h>
#include <vector>

// Random part
#define RandomX(x) (rand() % x)

namespace cpptools {

inline void SetRandomSeed(unsigned int seed) {
    srand(seed);
}

inline void SetRandomSeed() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec);
}

inline bool RandomBool() {
    if (RandomX(2) == 1) {
        return true;
    } else {
        return false;
    }
}

inline int RandomInt(int range) {
    return RandomX(range);
}
inline float RandomFloat() {
    return RandomInt(1000000) * 1.0 / 1000000;
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

extern std::vector<std::string> COLORS;

void PrintInfo(std::string str, INFO_TYPE info_type = INFO_TYPE::OK);

// File tools

std::vector<std::string> GetFiles(std::string dir, std::string pattern = "");
std::vector<std::string> Split(const std::string& s, const std::string& seperator);
std::string&             Replace_all(std::string& str, const std::string& old_value, const std::string& new_value);
std::string              CombinePath(std::vector<std::string> paths); ///< combine sub-path into path.
bool                     IsExist(std::string filename);               ///< Check folder exist.
bool                     CreateFodler(std::string foldername);        ///< Create folder.
bool                     DeleteFolder(std::string foldername);        ///< Delete folder.

// Timer
using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Timer {
  private:
    time_point st;   // start time point;
    time_point now;  // start time point;
    time_point last; // start time point;

  public:
    Timer();

    ~Timer();

    void Start();

    double StopMS();

    double StopUS();
};

inline double GetTimerMS(time_point t1, time_point t2);

inline double GetTimerUS(time_point t1, time_point t2);

// Simpele std::Any in c++17
class PlaceHolder {
  public:
    PlaceHolder() {}

    virtual ~PlaceHolder() {}

    virtual PlaceHolder* clone() = 0;
};

template <typename ValueType>
class Holder : public PlaceHolder {
  public:
    Holder() {}

    Holder(const ValueType& value)
        : _held(value) {}

    ~Holder() {}

    virtual PlaceHolder* clone() override {
        return new Holder(_held);
    }

  public:
    ValueType _held; // real data.
};

class Any {
  private:
    PlaceHolder* content_; // pointer to the real data.

  public:
    Any()
        : content_(nullptr) {
    }

    template <typename ValueType>
    Any(const ValueType& value)
        : content_(new Holder<ValueType>(value)) {
    }

    Any(const Any& other)
        : content_(other.content_ ? other.content_->clone() : nullptr) {
    }

    Any& operator=(const Any& other) {
        content_ = other.content_ ? other.content_->clone() : nullptr;
        return *this;
    }

    ~Any() {
        delete content_;
    }

    template <typename ValueType>
    ValueType get() {
        if (content_) {
            return static_cast<Holder<ValueType>*>(content_)->_held;
        } else {
            return 0;
        }
    }
};

}; // namespace cpptools

#endif

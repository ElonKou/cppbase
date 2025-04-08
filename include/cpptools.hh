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

// use "\033" replace "\e"
#define NONEC "\033[0m"
#define BLACK "\033[0;30m"
#define L_BLACK "\033[1;30m"
#define RED "\033[0;31m"
#define L_RED "\033[1;31m"
#define GREEN "\033[0;32m"
#define L_GREEN "\033[1;32m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[0;34m"
#define L_BLUE "\033[1;34m"
#define PURPLE "\033[0;35m"
#define L_PURPLE "\033[1;35m"
#define CYAN "\033[0;36m"
#define L_CYAN "\033[1;36m"
#define GRAY "\033[0;37m"
#define WHITE "\033[1;37m"

#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define REVERSE "\033[7m"
#define HIDE "\033[8m"
#define CLEAR "\033[2J"
#define CLRLINE "\r\033[K"
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

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

// Random part
#define RandomX(x) (rand() % x)

namespace cppt {

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

inline float RandomFloat(float v = 1.0f) {
    return RandomInt(1000000) * v / 1000000;
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

#include <cassert>
#include <cstring>
#include <iostream>

// ShortString
template <size_t N>
class ShortString {
    static_assert(N >= 1, "N must be greater than or equal to 1");

  protected:
    char data[N] = {'\0'};

  public:
    // default constructor
    ShortString() {
        data[0] = '\0';
    }

    // copy constructor: with c style input
    ShortString(char other) {
        data[0] = other;
        data[1] = '\0';
    }

    // copy constructor: with c style input
    ShortString(const char* other) {
        strncpy(data, other, N);
        data[N - 1] = '\0';
    }

    // copy constructor
    ShortString(const ShortString& other) {
        strncpy(data, other.data, N);
        data[N - 1] = '\0';
    }

    // copy constructor
    ShortString(const std::string& other) {
        size_t n = std::min(N, other.size() + 1);
        strncpy(data, other.c_str(), n);
        data[n - 1] = '\0';
    }

    // assign operator: for different ShortString
    template <size_t M>
    ShortString& operator=(const ShortString<M>& other) {
        if ((void*)this != (void*)&other) {
            if (N < M) {
                strncpy(data, other.c_str(), N);
                data[N - 1] = '\0';
            } else {
                strncpy(data, other.c_str(), M);
                data[M - 1] = '\0';
            }
        }
        return *this;
    }

    // assign operator: for std::string
    ShortString& operator=(const std::string& other) {
        size_t n = std::min(N, other.size() + 1);
        strncpy(data, other.c_str(), n);
        data[n - 1] = '\0';
        return *this;
    }

    // assign operator: for c style string
    ShortString& operator=(const char* other) {
        size_t n = std::min(N, strlen(other));
        strncpy(data, other, n);
        data[n - 1] = '\0';
        return *this;
    }

    // operator of index
    char& operator[](size_t index) {
        return data[index];
    }

    // operator of index
    char& at(size_t index) {
        assert(index < N && "Index out of bounds");
        return data[index];
    }

    // get size of ShortString
    size_t size() const {
        return strlen(data);
    }

    // get capacity of ShortString
    size_t capacity() const {
        return N;
    }

    // get data pointer of c style
    inline const char* c_str() const {
        return data;
    }

    ~ShortString() {}

    friend std::ostream& operator<<(std::ostream& os, const ShortString& str) {
        os << str.data;
        // os << str.data << "[" << N << "]";
        return os;
    }
};

using str8  = ShortString<8>;
using str16 = ShortString<16>;
using str32 = ShortString<32>;
using str64 = ShortString<64>;

// print color strings
enum INFO_TYPE : size_t {
    SUCCEED, // GREEN
    INFO,    // BLACK
    WARNING, // BROWN
    ERROR,   // RED
    FATAL,   // RED
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

// extern std::vector<std::string> COLORS; // cause memory leaky for twice free
inline std::string GetColors(INFO_TYPE type) {
    static std::vector<std::string> COLORS = {
        GREEN, CYAN, BROWN, RED, RED, RED, GREEN, BLUE, BLACK, BROWN, YELLOW, PURPLE, CYAN, GRAY, WHITE};
    return COLORS[type];
}

void PrintInfo(std::string str, INFO_TYPE info_type = INFO_TYPE::INFO);

// UUID Generator, more complate methods can use
inline std::string generate_uuid4() {
    // 使用随机生成器生成UUID
    boost::uuids::uuid uuid = boost::uuids::random_generator()();

    // 转换为字符串并返回
    auto str = boost::uuids::to_string(uuid);

    // 8-4-4-4-12
    // 550e8400-e29b-41d4-a716-446655440000
    // 前8位： 时间戳的高位部分，表示UUID生成的粗略时间。
    // 中间4位： 时间戳的低位部分，进一步细化时间。
    // 中间4位： 时钟序列，用于同一毫秒内生成的多个UUID的区分。
    // 中间4位： 版本号，标识UUID的生成方式。
    // 最后12位： 随机或伪随机数，保证UUID的唯一性。

    return str;
}

inline std::string generate_uuid4_12() {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    auto               str  = boost::uuids::to_string(uuid);
    return str.substr(24, 12); // 8-4-4-4-12
}

// File tools
std::vector<std::string> GetFilePath(std::string path);
std::vector<std::string> GetFiles(std::string dir, std::string pattern = "");
std::vector<std::string> Split(const std::string& s, const std::string& seperator);
std::string              Replace_all(const std::string& str, const std::string& old_value, const std::string& new_value);
std::string              CombinePath(std::vector<std::string> paths); ///< combine sub-path into path.
bool                     IsExist(std::string filename);               ///< Check folder exist.
bool                     CreateFodler(std::string foldername);        ///< Create folder.
bool                     DeleteFolder(std::string foldername);        ///< Delete folder.

// Timer and Tools
using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
inline double GetTimerMS(time_point t1, time_point t2);
inline double GetTimerUS(time_point t1, time_point t2);
std::time_t   GetNowTime();
std::string   ConvertTime2Str(std::time_t tm, bool hasyear = false);

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

    double GetRelativeTime();

    double GetAbstractTime();
};

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

// Matrix
template <typename T>
class Matrix {
  private:
    T*     data;
    size_t rows;
    size_t cols;

  protected:
    void AllocMem() {
        if (rows * cols != 0) {
            try {
                data = new T[rows * cols];
            } catch (const std::bad_alloc& e) {
                std::cerr << "Matrix: Memory allocation failed: " << e.what() << '\n';
            }
            std::memset((void*)data, 0, rows * cols * sizeof(T));
        } else {
            std::cout << "Items counts is zeno." << '\n';
        }
    }

  public:
    Matrix()
        : data(nullptr)
        , rows(0)
        , cols(0) {
    }

    Matrix(size_t rows, size_t cols)
        : rows(rows)
        , cols(cols) {
        AllocMem();
    }

    Matrix(size_t rows, size_t cols, T* data_ptr)
        : rows(rows)
        , cols(cols) {
        AllocMem();
        std::memcpy((void*)data, (void*)data_ptr, rows * cols * sizeof(T));
    }

    Matrix(size_t rows, size_t cols, const std::vector<T>& vec_data)
        : rows(rows)
        , cols(cols) {
        AllocMem();
        size_t min_size = std::min(rows * cols, vec_data.size());
        std::memcpy((void*)data, (void*)vec_data.data(), min_size * sizeof(T)); // clmap might happened.
    }

    Matrix(const Matrix& other)
        : rows(other.rows)
        , cols(other.cols) {
        AllocMem();
        std::memcpy((void*)data, (void*)other.data, rows * cols * sizeof(T)); // clmap when size dismatch.
    }

    ~Matrix() {
        delete[] data;
    }

    // 1-D data
    T& operator[](size_t index) {
        if (index >= rows * cols) {
            throw std::out_of_range("Matrix: Index out of range.");
        }
        return data[index];
    }

    // 2-D data for const.
    const T& operator()(size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix: Index out of range.");
        }
        return data[row * cols + col];
    }

    // 2-D data
    T& operator()(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix: Index out of range.");
        }
        return data[row * cols + col];
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            delete[] data;

            rows = other.rows;
            cols = other.cols;
            AllocMem();
            std::memcpy((void*)data, (void*)other.data, rows * cols * sizeof(T));
        }
        return *this;
    }

    // Get rows
    inline size_t GetRows() {
        return rows;
    }

    // Get cols
    inline size_t GetCols() {
        return cols;
    }

    inline void SetData(T* data_ptr) {
        if (data != data_ptr) {
            std::memcpy((void*)data, (void*)data_ptr, rows * cols * sizeof(T));
        }
    }

    inline void SetData(const std::vector<T>& vec_data) {
        size_t min_size = std::min(rows * cols, vec_data.size());
        std::memcpy((void*)data, (void*)vec_data.data(), min_size * sizeof(T)); // clmap might happened.
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (size_t i = 0; i < m.rows; i++) {
            for (size_t j = 0; j < m.cols; j++) {
                os << m(i, j) << " ";
            }
            if (i != (m.rows - 1)) {
                os << std::endl;
            }
        }
        return os;
    }
};

} // namespace cppt

#endif

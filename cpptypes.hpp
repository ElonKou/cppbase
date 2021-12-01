/*
 * version: 1.0
 */
#pragma once
#ifndef CPPTYPES_HH_
#define CPPTYPES_HH_

#include <cstring>
#include <iostream>
#include <ostream>

namespace cpptypes {

// vec2
template <typename T>
union vec2 {
    struct {
        T x;
        T y;
    };
    struct {
        T u;
        T v;
    };
    struct {
        T cols;
        T rows;
    };
    struct {
        T width;
        T height;
    };
    T value[2];

    // default cnstructor.
    vec2()
        : x(0)
        , y(0) {}

    // with input data constructor.
    vec2(T x_, T y_)
        : x(x_)
        , y(y_) {}

    // Other type cnstructor.
    template <typename Tp>
    vec2(Tp x_, Tp y_)
        : x((T)x_)
        , y((T)y_) {}

    // Other vec2 constructor
    template <typename Tp>
    vec2(const vec2<Tp>& o)
        : x((T)o.x)
        , y((T)o.y) {
    }

    // T* pointer constructor.
    vec2(const T* ptr) {
        if (ptr) {
            x = *ptr;
            y = *(ptr + 1);
        }
    }

    // Other Tp* pointer constructor.
    template <typename Tp>
    vec2(const Tp* ptr) {
        if (ptr) {
            x = (T)*ptr;
            y = (T) * (ptr + 1);
        }
    }

    // void* pointer constructor.
    vec2(const void* ptr) {
        if (ptr) {
            x = *((T*)ptr);
            y = *((T*)ptr + sizeof(T));
        }
    }

    ~vec2() {}

    template <typename Tp>
    vec2 operator+(const vec2<Tp>& other) {
        return vec2<T>(x + other.x, y + other.y);
    }

    template <typename Tp>
    vec2 operator-(const vec2<Tp>& other) {
        return vec2<T>(x - other.x, y - other.y);
    }

    template <typename Tp>
    vec2 operator*(const Tp& other) {
        return vec2<T>(x * other, y * other);
    }

    template <typename Tp>
    T operator*(const vec2<Tp>& other) {
        return x * other.x + y * other.y;
    }

    template <typename Tp>
    vec2 operator/(const Tp& other) {
        return vec2<T>(x / other, y / other);
    }

    friend std::ostream& operator<<(std::ostream& os, const vec2& v) {
        os << "[" << v.x << "," << v.y << "]";
        return os;
    }
};

template <typename T>
bool operator==(const vec2<T>& first, const vec2<T>& second) {
    return first.x == second.x && first.y == second.y;
}

template <typename T>
bool operator!=(const vec2<T>& first, const vec2<T>& second) {
    return first.x != second.x || first.y != second.y;
}

// vec3
template <typename T>
union vec3 {
    struct {
        T x;
        T y;
        T z;
    };
    struct {
        T u;
        T v;
        T w;
    };
    struct {
        T cols;
        T rows;
        T pals;
    };
    struct {
        T r;
        T g;
        T b;
    };
    struct {
        T width;
        T height;
        T channel;
    };
    T value[3];

    // default cnstructor.
    vec3()
        : x(0)
        , y(0)
        , z(0) {}

    // with input data constructor.
    vec3(T x_, T y_, T z_)
        : x(x_)
        , y(y_)
        , z(z_) {}

    // Other type cnstructor.
    template <typename Tp>
    vec3(Tp x_, Tp y_, Tp z_)
        : x((T)x_)
        , y((T)y_)
        , z((T)z_) {}

    // Other vec3 constructor
    template <typename Tp>
    vec3(const vec3<Tp>& o)
        : x((T)o.x)
        , y((T)o.y)
        , z((T)o.z) {
    }

    // T* pointer constructor.
    vec3(const T* ptr) {
        if (ptr) {
            x = *ptr;
            y = *(ptr + 1);
            z = *(ptr + 2);
        }
    }

    // Other Tp* pointer constructor.
    template <typename Tp>
    vec3(const Tp* ptr) {
        if (ptr) {
            x = (T)*ptr;
            y = (T) * (ptr + 1);
            z = (T) * (ptr + 2);
        }
    }

    // void* pointer constructor.
    vec3(const void* ptr) {
        if (ptr) {
            x = *((T*)ptr);
            y = *((T*)ptr + sizeof(T));
            z = *((T*)ptr + sizeof(T) + sizeof(T));
        }
    }

    vec3(const vec2<T>& v2, T z_ = T(1)) {
        x = v2.x;
        y = v2.y;
        z = z_;
    }

    ~vec3() {}

    template <typename Tp>
    vec3 operator+(const vec3<Tp>& other) {
        return vec3<T>(x + other.x, y + other.y, z + other.z);
    }

    template <typename Tp>
    vec3 operator-(const vec3<Tp>& other) {
        return vec3<T>(x - other.x, y - other.y, z - other.z);
    }

    template <typename Tp>
    vec3 operator*(const Tp& other) {
        return vec3<T>(x * other, y * other, z * other);
    }

    template <typename Tp>
    T operator*(const vec3<Tp>& other) {
        return x * other.x + y * other.y + z * other.z;
    }

    template <typename Tp>
    vec3 operator/(const Tp& other) {
        return vec3<T>(x / other, y / other, z / other);
    }

    friend std::ostream& operator<<(std::ostream& os, const vec3& v) {
        os << "[" << v.x << "," << v.y << "," << v.z << "]";
        return os;
    }
};

template <typename T>
bool operator==(const vec3<T>& first, const vec3<T>& second) {
    return first.x == second.x && first.y == second.y && first.z == second.z;
}

template <typename T>
bool operator!=(const vec3<T>& first, const vec3<T>& second) {
    return first.x != second.x || first.y != second.y || first.z != second.z;
}

// vec4
template <typename T>
union vec4 {
    struct {
        T x;
        T y;
        T z;
        T t;
    };
    struct {
        T cols;
        T rows;
        T pals;
        T voxs;
    };
    struct {
        T r;
        T g;
        T b;
        T a;
    };
    struct {
        T width;
        T height;
        T channel;
        T num;
    };

    T value[4];

    // default cnstructor.
    vec4()
        : x(0)
        , y(0)
        , z(0)
        , t(0) {}

    // with input data constructor.
    vec4(T x_, T y_, T z_, T t_)
        : x(x_)
        , y(y_)
        , z(z_)
        , t(t_) {}

    // Other type cnstructor.
    template <typename Tp>
    vec4(Tp x_, Tp y_, Tp z_, Tp t_)
        : x((T)x_)
        , y((T)y_)
        , z((T)z_)
        , t((T)t_) {}

    // Other vec4 constructor
    template <typename Tp>
    vec4(const vec4<Tp>& o)
        : x((T)o.x)
        , y((T)o.y)
        , z((T)o.z)
        , t((T)o.t) {
    }

    // T* pointer constructor.
    vec4(const T* ptr) {
        if (ptr) {
            x = *ptr;
            y = *(ptr + 1);
            z = *(ptr + 2);
            t = *(ptr + 3);
        }
    }

    // Other Tp* pointer constructor.
    template <typename Tp>
    vec4(const Tp* ptr) {
        if (ptr) {
            x = (T)*ptr;
            y = (T) * (ptr + 1);
            z = (T) * (ptr + 2);
            t = (T) * (ptr + 3);
        }
    }

    // void* pointer constructor.
    vec4(const void* ptr) {
        if (ptr) {
            x = *((T*)ptr);
            y = *((T*)ptr + sizeof(T));
            z = *((T*)ptr + sizeof(T) + sizeof(T));
            t = *((T*)ptr + sizeof(T) + sizeof(T) + sizeof(T));
        }
    }

    vec4(const vec2<T>& v21, const vec2<T>& v22) {
        x = v21.x;
        y = v21.y;
        z = v22.x;
        t = v22.y;
    }

    vec4(const vec3<T> v3, T t_ = T(1)) {
        x = v3.x;
        y = v3.y;
        z = v3.z;
        t = t_;
    }

    ~vec4() {}

    template <typename Tp>
    vec4 operator+(const vec4<Tp>& other) {
        return vec4<T>(x + other.x, y + other.y, z + other.z, t + other.t);
    }

    template <typename Tp>
    vec4 operator-(const vec4<Tp>& other) {
        return vec4<T>(x - other.x, y - other.y, z - other.z, t - other.t);
    }

    template <typename Tp>
    vec4 operator*(const Tp& other) {
        return vec4<T>(x * other, y * other, z * other, t * other);
    }

    template <typename Tp>
    T operator*(const vec4<Tp>& other) {
        return x * other.x + y * other.y + z * other.z + t * other.t;
    }

    template <typename Tp>
    vec4 operator/(const Tp& other) {
        return vec4<T>(x / other, y / other, z / other, t / other);
    }

    friend std::ostream& operator<<(std::ostream& os, const vec4& v) {
        os << "[" << v.x << "," << v.y << "," << v.z << "," << v.t << "]";
        return os;
    }
};

template <typename T>
bool operator==(const vec4<T>& first, const vec4<T>& second) {
    return first.x == second.x && first.y == second.y && first.z == second.z && first.t == second.t;
}

template <typename T>
bool operator!=(const vec4<T>& first, const vec4<T>& second) {
    return first.x != second.x || first.y != second.y || first.z != second.z || first.t != second.t;
}

// vector 2d
typedef vec2<char>          vec2c;
typedef vec2<unsigned char> vec2uc;
typedef vec2<size_t>        vec2s;
typedef vec2<int>           vec2i;
typedef vec2<unsigned int>  vec2ui;
typedef vec2<float>         vec2f;
typedef vec2<double>        vec2d;

// vector 3d
typedef vec3<char>          vec3c;
typedef vec3<unsigned char> vec3uc;
typedef vec3<size_t>        vec3s;
typedef vec3<int>           vec3i;
typedef vec3<unsigned int>  vec3ui;
typedef vec3<float>         vec3f;
typedef vec3<double>        vec3d;

// vector 4d
typedef vec4<char>          vec4c;
typedef vec4<unsigned char> vec4uc;
typedef vec4<size_t>        vec4s;
typedef vec4<int>           vec4i;
typedef vec4<unsigned int>  vec4ui;
typedef vec4<float>         vec4f;
typedef vec4<double>        vec4d;

// Dimension
typedef vec2s Dim2; // Dimension2
typedef vec3s Dim3; // Dimension3
typedef vec4s Dim4; // Dimension4

// Point 2d
typedef vec2i Point2i; // Point2
typedef vec2f Point2f; // Point2
typedef vec2d Point2d; // Point2

// Point 3d
typedef vec3i Point3i; // Point3
typedef vec3f Point3f; // Point3
typedef vec3d Point3d; // Point3

// Point 4d
typedef vec4i Point4i; // Point4
typedef vec4f Point4f; // Point4
typedef vec4d Point4d; // Point4

// Mat2
template <typename Tp>
class mat2 {
  public:
    Dim2   dim;  // dimension of data.
    size_t size; // record data counts of type Tp.
    Tp*    ptr;  // pointer for data.

    mat2()
        : dim(Dim2())
        , size(0)
        , ptr(nullptr) {
    }

    mat2(Dim2 dim_)
        : dim(dim_)
        , size(dim.x * dim.y)
        , ptr(nullptr) {
        if (size != 0) {
            ptr = new Tp(size * sizeof(Tp));
            memset((void*)ptr, 0, size * sizeof(Tp));
            if (!ptr) {
                std::cout << "ERROR: create mat2..." << std::endl;
            }
        }
    }

    Tp& operator[](const Dim2 pos) {
        return ptr[pos.y * dim.width + pos.x];
    }

    Tp* operator[](const size_t p) {
        return ptr + p * dim.width;
    }

    Tp& get(size_t x, size_t y) {
        return ptr[y * dim.width + x];
    }

    ~mat2() {
    }

    void seteyes() {
        int c = dim.width > dim.height ? dim.height : dim.width;
        for (size_t i = 0; i < c; i++) {
            (*this)[i][i] = (Tp)1;
        }
    }

    void setones() {
        for (size_t i = 0; i < size; i++) {
            (*this).ptr[i] = (Tp)1;
        }
    }

    void setlines() {
        for (size_t i = 0; i < size; i++) {
            (*this).ptr[i] = (Tp)i;
        }
    }

    void reshape(Dim2 d) {
        if (size == d.x * d.y) {
            dim = d;
        } else {
            std::cout << "dim: " << dim << " can't be reshape into dim: " << d << std::endl;
        }
    }

    void T() {
        Tp tmp[size];
        for (size_t j = 0; j < dim.width; j++) {
            for (size_t i = 0; i < dim.height; i++) {
                tmp[j * dim.height + i] = ptr[i * dim.width + j];
            }
        }
        dim = Dim2(dim.y, dim.x);
        for (size_t i = 0; i < size; i++) {
            ptr[i] = tmp[i];
        }
    }

    vec2<Tp> getrows(const size_t& row) {
        return vec2<Tp>(ptr[row * dim.width], ptr[row * dim.width + 1]);
    }

    vec2<Tp> getcols(const size_t& col) {
        return vec2<Tp>(ptr[col], ptr[col + dim.width]);
    }

    friend std::ostream& operator<<(std::ostream& os, mat2& m) {
        if (m.ptr) {
            std::cout << m.dim << " " << std::endl;
            for (size_t i = 0; i < m.dim.height; i++) {
                for (size_t j = 0; j < m.dim.width; j++) {
                    os << m[i][j] << " ";
                }
                if (i != m.dim.height - 1) {
                    os << std::endl;
                }
            }
        }
        return os;
    }
};

// Mat3
template <typename Tp>
class mat3 {
  public:
    Dim3   dim;  // dimension of data.
    size_t size; // record data counts of type Tp.
    Tp*    ptr;  // pointer for data.

    mat3()
        : dim(Dim3())
        , size(0)
        , ptr(nullptr) {
    }

    mat3(Dim3 dim_)
        : dim(dim_)
        , size(dim.x * dim.y * dim.z)
        , ptr(nullptr) {
        if (size != 0) {
            ptr = new Tp(size * sizeof(Tp));
            memset((void*)ptr, 0, size * sizeof(Tp));
            if (!ptr) {
                std::cout << "ERROR: create mat3..." << std::endl;
            }
        }
    }

    Tp& operator[](const Dim3 pos) {
        return ptr[pos.z * dim.width * dim.height + pos.y * dim.width + pos.x];
    }

    Tp& get(size_t x, size_t y, size_t z) {
        return ptr[z * dim.width * dim.height + y * dim.width + x];
    }

    ~mat3() {
    }

    void setones() {
        for (size_t i = 0; i < size; i++) {
            (*this).ptr[i] = (Tp)1;
        }
    }

    void setlines() {
        for (size_t i = 0; i < size; i++) {
            (*this).ptr[i] = (Tp)i;
        }
    }

    void reshape(Dim3 d) {
        if (size == d.x * d.y * d.z) {
            dim = d;
        } else {
            std::cout << "dim: " << dim << " can't be reshape into dim: " << d << std::endl;
        }
    }

    // TODO: has bug
    mat2<Tp> getrows(const size_t& row) {
        if (row) {
            // return vec2<Tp>(ptr[row * dim.width], ptr[row * dim.width + 1]);
        } else {
            return mat2<Tp>(Dim2(0, 0));
        }
    }

    // TODO: has bug
    mat2<Tp> getcols(const size_t& col) {
        if (col < dim.width) {
            mat2<Tp> tmp(Dim2(dim.pals, dim.height));
            for (size_t i = 0; i < dim.height; i++) {
                for (size_t j = 0; j < dim.pals; j++) {
                    tmp[i][j] = get(col, i, j);
                }
            }
            return tmp;
        } else {
            return mat2<Tp>(Dim2(0, 0));
        }
    }
    // TODO: has bug
    mat2<Tp> getpals(const size_t& pal) {
        if (pal < dim.channel) {
            mat2<Tp> tmp(Dim2(dim.width, dim.height));
            memcpy((void*)tmp.ptr, (void*)(ptr + dim.width * dim.height * pal), dim.width * dim.height * sizeof(Tp));
            return tmp;
        } else {
            return mat2<Tp>(Dim2(0, 0));
        }
    }

    friend std::ostream& operator<<(std::ostream& os, mat3& m) {
        if (m.ptr) {
            std::cout << m.dim << " " << std::endl;
            for (size_t k = 0; k < m.dim.pals; k++) {
                for (size_t i = 0; i < m.dim.height; i++) {
                    for (size_t j = 0; j < m.dim.width; j++) {
                        os << m.get(j, i, k) << " ";
                    }
                    os << std::endl;
                }
                if (k != m.dim.pals - 1) {
                    os << std::endl;
                }
            }
        }
        return os;
    }
};

// mat 2-d
typedef mat2<char>          Mat2c;
typedef mat2<unsigned char> Mat2uc;
typedef mat2<int>           Mat2i;
typedef mat2<unsigned int>  Mat2ui;
typedef mat2<float>         Mat2f;
typedef mat2<double>        Mat2d;

// mat 3-d
typedef mat3<char>          Mat3c;
typedef mat3<unsigned char> Mat3uc;
typedef mat3<int>           Mat3i;
typedef mat3<unsigned int>  Mat3ui;
typedef mat3<float>         Mat3f;
typedef mat3<double>        Mat3d;

} // namespace cpptypes

#endif

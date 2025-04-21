#pragma once

#include <iosfwd>
#include <vector>
#include <ostream>
#include <stdexcept>

namespace gnssRecv
{
namespace math
{

template<typename T>
std::vector<T> operator*(const T &k, const std::vector<T> &b){
    std::vector<T> res(b.size());
    for (size_t i = 0; i < b.size(); ++i) {
        res[i] = b[i] * k;
    }
    return res;
};

template<typename T>
std::vector<T> operator*(const std::vector<T> &b, const T &k){
    return k * b;
};

template<typename T>
T operator*(const std::vector<T> &a, const std::vector<T> &b){
    T res = 0;
    for (int i = 0; i < a.size(); ++i) {
        res += a[i] * b[i];
    }
    return res;
};

template<typename T>
std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b){
    std::vector<T> res(a.size());
    for(int i = 0; i < a.size(); ++i){
        res[i] = a[i] - b[i];
    }
    return res;
};

template<typename T>
std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b){
    return a - static_cast<T>(-1) * b;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &b){
    for (auto i: b) {
        os << i << " ";
    }
    os << "\n";
    return os;
};

} //namespace math

} //namespace gnssRecv
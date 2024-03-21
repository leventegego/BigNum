#ifndef DIGITSTR
#define DIGITSTR

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include "bigexc.h"

using ui = uint32_t;
using ul = uint64_t;

// arbitrarily large non-negative integer
class natural
{

private:

    // each uint32 is a 'digit' base 2^32
    // digit vector is little endian (digits are indexed from least significant to most)
    // such digit vectors are used throughout this class to store numbers
    std::vector<ui> v;

    static void add_digit(ui d1, ui d2, ui &ans, ui &carry);
    static void sub_digit(ui d1, ui d2, ui &ans, ui &carry);
    static void mul_digit(ui d1, ui d2, ui &ans, ui &carry);

    static void add(std::vector<ui> &v1, const std::vector<ui> &v2, size_t sh); // v1 <- v1 + (v2 << sh)
    static void sub(std::vector<ui> &v1, const std::vector<ui> &v2, size_t sh); // v1 <- v1 - (v2 << sh) where v1 >= (v2 << sh)
    static void mul(const std::vector<ui> &v1, const std::vector<ui> &v2, std::vector<ui> &ans); // ans <- v1 * v2
    static void div(const std::vector<ui> &v1, const std::vector<ui> &v2,
        std::vector<ui> &ans,  // ans <- v1 / v2
        std::vector<ui> &rem); // rem <- v1 % v2

    static void shl(std::vector<ui> &v, bool in); // v <<= 1 bit
    static size_t msbi(const std::vector<ui> &v); // index of most significant 1 bit in v

    static int comp(const std::vector<ui> &v1, const std::vector<ui> &v2);

    static void trim(std::vector<ui> &v); // remove leading zero digits from vector

    natural(const std::initializer_list<ui> &x);


public:

    natural();
    natural(ul x);
    natural(const natural &other) = default;
    natural(natural &&other);
    natural &operator=(const natural &other) = default;
    natural &operator=(natural &&other);

    explicit operator bool() const; // not 0
    ul operator%(ul lhs) const; // use to convert to basic integers

    static int comp(const natural &s1, const natural &s2);

    natural &operator+=(const natural &x);
    natural &operator-=(const natural &x);

    friend natural operator*(const natural &s1, const natural &s2);
    friend natural operator/(const natural &s1, const natural &s2);
    friend natural operator%(const natural &s1, const natural &s2);

};


#endif


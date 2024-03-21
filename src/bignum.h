#ifndef BIGNUM
#define BIGNUM

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdint>
#include <cctype>
#include <algorithm>
#include "natural.h"


// arbitrarily large integer
class bignum
{
private:

    // bignum is a wrapper around natural, that handles
    // signedness and provides a more extensive interface
    natural num;
    bool sign; // true -> negative


public:

    static int comp(const bignum &a, const bignum &b);

    bignum();
    bignum(int x);
    explicit bignum(const std::string &str);
    friend bignum operator""_big(const char *str);

    bignum(const bignum &other) = default;
    bignum(bignum &&other);
    bignum &operator=(const bignum &other) = default;
    bignum &operator=(bignum &&other);

    static bool valid(const std::string &str);
    explicit operator std::string() const;
    friend std::ostream &operator<<(std::ostream &os, const bignum &x);
    friend std::istream &operator>>(std::istream &is, bignum &x);

    friend bool operator==(const bignum &a, const bignum &b);
    friend bool operator< (const bignum &a, const bignum &b);
    friend bool operator<=(const bignum &a, const bignum &b);
    friend bool operator> (const bignum &a, const bignum &b);
    friend bool operator>=(const bignum &a, const bignum &b);


    bignum &operator+=(const bignum &x);
    bignum &operator-=(const bignum &x);
    bignum &operator*=(const bignum &x);
    bignum &operator/=(const bignum &x);

    friend bignum operator+(const bignum &a, const bignum &b);
    friend bignum operator-(const bignum &a, const bignum &b);
    friend bignum operator*(const bignum &a, const bignum &b);
    friend bignum operator/(const bignum &a, const bignum &b);

    friend bignum operator+(const bignum &x);
    friend bignum operator-(const bignum &x);

};




#endif


#include "bignum.h"

int bignum::comp(const bignum &a, const bignum &b)
{
    if(a.sign && !b.sign) return -1;
    if(!a.sign && b.sign) return 1;

    int c = natural::comp(a.num, b.num);
    return (a.sign ? -c : c);
}

bignum::bignum() : num(0), sign(false) {}
bignum::bignum(int x) : num(std::abs(x)), sign(x < 0) { }
bignum::bignum(const std::string &str) : num(0), sign(str[0] == '-')
{
    for(size_t i = sign; i < str.size(); ++i)
    {
        num = num * 10;
        num += str[i] - '0';
    }
    if(!num)
        sign = false;
}

bignum::bignum(bignum &&other) : num(std::move(other.num)), sign(other.sign) { }
bignum &bignum::operator=(bignum &&other) { num = std::move(other.num); sign = other.sign; return *this; }

bool bignum::valid(const std::string &str)
{
    if(str.size() == 0)
        return false;

    bool sign = (str[0] == '-');
    if(sign && str.size() == 1)
        return false;

    return std::all_of(str.begin() + sign, str.end(), ::isdigit);
}

bignum::operator std::string() const
{
    if(!num)
        return "0";

    std::string r;
    for(natural copy = num; copy; copy = copy / 10)
        r += (copy % 10) + '0';
    if(sign)
        r += '-';
    std::reverse(r.begin(), r.end());
    return r;
}

bignum &bignum::operator+=(const bignum &x) { return *this = *this + x; }
bignum &bignum::operator-=(const bignum &x) { return *this = *this - x; }
bignum &bignum::operator*=(const bignum &x) { return *this = *this * x; }
bignum &bignum::operator/=(const bignum &x) { return *this = *this / x; }

bignum operator""_big(const char *str) { return bignum(str); }

std::ostream &operator<<(std::ostream &os, const bignum &x) { return os << (std::string)x; }
std::istream &operator>>(std::istream &is, bignum &x) { std::string s; is >> s; x = bignum(s.c_str()); return is; }

bool operator==(const bignum &a, const bignum &b) { return bignum::comp(a, b) == 0; }
bool operator< (const bignum &a, const bignum &b) { return bignum::comp(a, b) <  0; }
bool operator<=(const bignum &a, const bignum &b) { return bignum::comp(a, b) <= 0; }
bool operator> (const bignum &a, const bignum &b) { return bignum::comp(a, b) >  0; }
bool operator>=(const bignum &a, const bignum &b) { return bignum::comp(a, b) >= 0; }

bignum operator+(const bignum &a, const bignum &b)
{
    if(a.sign ^ b.sign)
    {
        int c = natural::comp(a.num, b.num);
        const bignum &x = (c >= 0 ? a : b);
        const bignum &y = (c >= 0 ? b : a);

        bignum r = x;
        r.num -= y.num;
        r.sign = x.sign && r.num;
        return r;
    }
    else
    {
        bignum r = a;
        r.num += b.num;
        r.sign = a.sign;
        return r;
    }
}
bignum operator-(const bignum &a, const bignum &b)
{
    return a + (-b);
}

bignum operator*(const bignum &a, const bignum &b)
{
    bignum r;
    r.num = a.num * b.num;
    r.sign = a.sign ^ b.sign && r.num;
    return r;
}
bignum operator/(const bignum &a, const bignum &b)
{
    bignum r;
    r.num = a.num / b.num;
    r.sign = a.sign ^ b.sign && r.num;
    return r;
}

bignum operator+(const bignum &x) { return x; }
bignum operator-(const bignum &x) { bignum r(x); r.sign ^= 1; return r; }


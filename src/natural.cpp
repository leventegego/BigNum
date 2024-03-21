#include "natural.h"



void natural::add_digit(ui d1, ui d2, ui &ans, ui &carry)
{
    ul x = (ul)d1 + d2;
    ans = x;
    carry = x >> 32;
}

void natural::sub_digit(ui d1, ui d2, ui &ans, ui &carry)
{
    ul x = (ul)d1 - d2;
    ans = x;
    carry = (ui)0 - (x >> 32);
}

void natural::mul_digit(ui d1, ui d2, ui &ans, ui &carry)
{
    ul x = (ul)d1 * d2;
    ans = x;
    carry = x >> 32;
}

void natural::add(std::vector<ui> &v1, const std::vector<ui> &v2, size_t sh)
{
    size_t s2 = v2.size() + sh;
    v1.resize(std::max(v1.size(), s2), 0);

    ui carry = 0;
    for(size_t i = sh; i < s2; ++i)
    {
        ui carry1, carry2;
        add_digit(v1[i], carry,      v1[i], carry1);
        add_digit(v1[i], v2[i - sh], v1[i], carry2);
        carry = carry1 + carry2;
    }
    for(size_t i = s2; s2 < v1.size() && carry; ++i)
        add_digit(v1[i], carry, v1[i], carry);
    if(carry)
        v1.push_back(carry);
    trim(v1);
}

void natural::sub(std::vector<ui> &v1, const std::vector<ui> &v2, size_t sh)
{
    size_t s2 = v2.size() + sh;

    ui carry = 0;
    for(size_t i = sh; i < s2; ++i)
    {
        ui carry1, carry2;
        sub_digit(v1[i], carry,      v1[i], carry1);
        sub_digit(v1[i], v2[i - sh], v1[i], carry2);
        carry = carry1 + carry2;
    }
    for(size_t i = s2; carry; ++i)
        sub_digit(v1[s2], carry, v1[s2], carry);
    trim(v1);
}

void natural::mul(const std::vector<ui> &v1, const std::vector<ui> &v2, std::vector<ui> &ans)
{
    for(size_t i1 = 0; i1 < v1.size(); ++i1)
    for(size_t i2 = 0; i2 < v2.size(); ++i2)
    {
        std::vector<ui> prod(2);
        mul_digit(v1[i1], v2[i2], prod[0], prod[1]);
        trim(prod);
        add(ans, prod, i1 + i2);
    }
    trim(ans);
}

void natural::div(const std::vector<ui> &v1, const std::vector<ui> &v2, std::vector<ui> &ans, std::vector<ui> &rem)
{
    if(v2.empty())
        throw invalid_operation("div by zero!");

    // binary long division

    ans.resize(v1.size(), 0);
    for(size_t i = msbi(v1); i != (size_t)-1; --i)
    {
        size_t idigit = i / 32;
        size_t ibit = i % 32;
        shl(rem, (v1[idigit] >> ibit) & (ui)1); // shift i-th bit of v1 into rem
        if(comp(rem, v2) >= 0)
        {
            sub(rem, v2, 0);
            ans[idigit] |= ((ui)1 << ibit); // set i-th bit of ans
        }
    }
    trim(ans);
}

void natural::shl(std::vector<ui> &v, bool in)
{
    ui carry = in;
    for(size_t i = 0; i < v.size(); ++i)
    {
        ui carry_ = v[i] >> 31;
        v[i] = (v[i] << 1) | carry;
        carry = carry_;
    }
    if(carry)
        v.push_back(carry);
}

size_t natural::msbi(const std::vector<ui> &v)
{
    if(v.empty())
        return -1;

    size_t idigit = v.size() - 1;
    size_t ibit = 0;
    while(ibit < 32 && v[idigit] >> ibit)
        ++ibit;
    return idigit * 32 + ibit - 1;
}

int natural::comp(const std::vector<ui> &v1, const std::vector<ui> &v2)
{
    if(v1.size() < v2.size()) return -1;
    if(v1.size() > v2.size()) return 1;
    for(int i = v1.size() - 1; i >= 0; --i)
    {
        if(v1[i] < v2[i]) return -1;
        if(v1[i] > v2[i]) return 1;
    }
    return 0;
}

void natural::trim(std::vector<ui> &v)
{
    size_t i = v.size() - 1;
    while(i != (size_t)-1 && v[i] == 0)
        --i;
    v.erase(v.begin() + i + 1, v.end());
}

natural::natural(ul x) : natural({ (ui)x, (ui)(x >> 32) }) { }
natural::natural(natural &&other) { v.swap(other.v); }
natural &natural::operator=(natural &&other) { v.swap(other.v); return *this; }
natural::natural() {}
natural::natural(const std::initializer_list<ui> &x) : v(x) { trim(v); }

natural::operator bool() const { return !v.empty(); }

ul natural::operator%(ul lhs) const
{
    natural r = *this % (natural)lhs;
    if(r.v.size() == 0) return 0;
    if(r.v.size() == 1) return r.v[0];
    return (ul)r.v[1] << 32 | r.v[0];
}

int natural::comp(const natural &s1, const natural &s2) { return comp(s1.v, s2.v); }

natural &natural::operator+=(const natural &x) { add(v, x.v, 0); return *this; }
natural &natural::operator-=(const natural &x) { sub(v, x.v, 0); return *this; }

natural operator*(const natural &s1, const natural &s2)
    { natural r; natural::mul(s1.v, s2.v, r.v); return r; }
natural operator/(const natural &s1, const natural &s2)
    { natural r; std::vector<ui> rem; natural::div(s1.v, s2.v, r.v, rem); return r; }
natural operator%(const natural &s1, const natural &s2)
    { natural r; std::vector<ui> quo; natural::div(s1.v, s2.v, quo, r.v); return r; }

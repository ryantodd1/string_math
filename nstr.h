#ifndef NSTR_H
#define NSTR_H

#include <iostream>
#include <string>
#include <bits/stdc++.h>

class nstr
{
private:
    std::string number;
    bool neg;

protected:
    static int precision;
    static int disp_precision;

public:
    nstr();
    nstr(const char*);
    nstr(const std::string&);
    nstr(const nstr&);
    ~nstr();

    static void set_precision(int);
    static void set_disp_precision(int);

    friend std::ostream& operator<<(std::ostream&, nstr);

    friend nstr operator+(const nstr&, const nstr&);
    friend nstr operator*(const nstr&, const nstr&);
    friend nstr operator-(const nstr&, const nstr&);
    friend nstr operator/(const nstr&, const nstr&);

    friend nstr operator+(const char*, const nstr&);
    friend nstr operator*(const char*, const nstr&);
    friend nstr operator-(const char*, const nstr&);
    friend nstr operator/(const char*, const nstr&);

    friend nstr operator+(const nstr&, const char*);
    friend nstr operator*(const nstr&, const char*);
    friend nstr operator-(const nstr&, const char*);
    friend nstr operator/(const nstr&, const char*);

    friend bool operator==(const nstr&, const nstr&);
    friend bool operator!=(const nstr&, const nstr&);
    friend bool operator>=(const nstr&, const nstr&);
    friend bool operator<=(const nstr&, const nstr&);
    friend bool operator>(const nstr&, const nstr&);
    friend bool operator<(const nstr&, const nstr&);

    friend bool operator==(const char*, const nstr&);
    friend bool operator!=(const char*, const nstr&);
    friend bool operator>=(const char*, const nstr&);
    friend bool operator<=(const char*, const nstr&);
    friend bool operator>(const char*, const nstr&);
    friend bool operator<(const char*, const nstr&);

    friend bool operator==(const nstr&, const char*);
    friend bool operator!=(const nstr&, const char*);
    friend bool operator>=(const nstr&, const char*);
    friend bool operator<=(const nstr&, const char*);
    friend bool operator>(const nstr&, const char*);
    friend bool operator<(const nstr&, const char*);

};

#endif
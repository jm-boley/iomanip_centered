#ifndef __IOMANIP_CENTERED_H
#define __IOMANIP_CENTERED_H
#pragma once
#include <string>
#include <iostream>
#include <iomanip>

/**
 * Adds the centered() formatter to the C++ std iomanip formatters. Attempts to center text in the output
 * stream. May be used alongside std::setw.
 * 
 * Usage:
 *   [std::basic_ostream] << setw(x) << centered([char*|std::string|numeric])
 * 
 * Examples:
 *   #include <sstream>
 *   #include "iomanip_centered.h"
 * 
 *   using std::cout;
 *   using std::setw;
 *   using std::endl;
 *   using std::ostringstream;
 *   
 *   // ...
 *
 *   // Print table column labels
 *   cout << setw(10) << centered("Column A") << setw(10) << centered("Column B") << endl;
 *   cout << setw(10) << centered("==========") << setw(10) << centered("==========") << endl;
 * 
 *   // Create formatted string of column values
 *   ostringstream oss;
 *   oss << setw(10) << centered("1") << setw(10) << centered(10.0f) << '\n';
 *   oss << setw(10) << centered("2") << setw(10) << centered('w') << '\n';
 *   oss << setw(10) << centered("3") << setw(10) << centered((signed char) -10) << '\n';
 *   oss << setw(10) << centered("4") << setw(10) << centered((unsigned char) 10) << '\n';
 *   cout << oss.str() << endl;
 * 
 * Changelog:
 * (3/19/2020) Modified operator<< overload to prevent signed-unsigned type comparison warnings
 *             - Joshua Boley (z1698317@students.niu.edu)
 * (3/21/2020) * Added support for the (signed and unsigned) short, int, long int, long long int,
 *               and float and double built-in data types
 *             * Added support for signed and unsigned char numeric type, standard (text) char
 *             - Joshua Boley (z1698317@students.niu.edu)
 * (3/22/2020) * Fixed bug with standard text char not rendering as text in the output stream
 *             * Include guards added
 *             - Joshua Boley (z1698317@students.niu.edu)
 * 
 * Original (unmodified) code retrieved from:
 * https://stackoverflow.com/questions/14861018/center-text-in-fixed-width-field-with-stream-manipulators-in-c
 * Contributed by stackoverflow user Lily Ballard
 */

template<typename charT, typename traits = std::char_traits<charT> >
class center_helper {
    std::basic_string<charT, traits> str_;
public:
    center_helper(std::basic_string<charT, traits> str) : str_(str) {}
    template<typename a, typename b>
    friend std::basic_ostream<a, b>& operator<<(std::basic_ostream<a, b>& s, const center_helper<a, b>& c);
};

template<typename charT, typename traits = std::char_traits<charT> >
center_helper<charT, traits> centered(std::basic_string<charT, traits> str) {
    return center_helper<charT, traits>(str);
}

// Redeclare for std::string directly so we can support anything that implicitly converts to std::string
center_helper<std::string::value_type, std::string::traits_type> centered(const std::string& str) {
    return center_helper<std::string::value_type, std::string::traits_type>(str);
}

// Redeclare for char
center_helper<std::string::value_type, std::string::traits_type> centered(char character) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::string(1, character));
}

// Redeclare for standard numeric types so we can support built-in data types
center_helper<std::string::value_type, std::string::traits_type> centered(signed char intval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(intval));
}

center_helper<std::string::value_type, std::string::traits_type> centered(unsigned char intval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(intval));
}

center_helper<std::string::value_type, std::string::traits_type> centered(short int intval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(intval));
}

center_helper<std::string::value_type, std::string::traits_type> centered(unsigned short int intval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(intval));
}

center_helper<std::string::value_type, std::string::traits_type> centered(int intval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(intval));
}

center_helper<std::string::value_type, std::string::traits_type> centered(unsigned int intval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(intval));
}

center_helper<std::string::value_type, std::string::traits_type> centered(long int intval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(intval));
}

center_helper<std::string::value_type, std::string::traits_type> centered(unsigned long int intval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(intval));
}

center_helper<std::string::value_type, std::string::traits_type> centered(long long int intval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(intval));
}

center_helper<std::string::value_type, std::string::traits_type> centered(unsigned long long int intval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(intval));
}

center_helper<std::string::value_type, std::string::traits_type> centered(float floatval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(floatval));
}

center_helper<std::string::value_type, std::string::traits_type> centered(double floatval) {
    return center_helper<std::string::value_type, std::string::traits_type>(std::to_string(floatval));
}

template<typename charT, typename traits>
std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& s, const center_helper<charT, traits>& c) {
    std::streamsize w = s.width();
    if (static_cast<size_t>(w) > c.str_.length()) {
        std::streamsize left = (w + c.str_.length()) / 2;
        s.width(left);
        s << c.str_;
        s.width(w - left);
        s << "";
    } else {
        s << c.str_;
    }
    return s;
}

#endif

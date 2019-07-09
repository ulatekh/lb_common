#pragma once

#include <istream>

#include <streambuf>
#include <string_view>


inline bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

inline void trim_whitespace(std::string_view & sv) {
    while(false == sv.empty() && is_whitespace(sv.front())) {
        sv.remove_prefix(1);
    }
    while(false == sv.empty() && is_whitespace(sv.back())) {
        sv.remove_suffix(1);
    }
}

inline bool starts_with(const std::string_view haystack, const std::string_view needle) {
    if(haystack.size() < needle.size()) {
        return false;
    }
    return std::equal(needle.cbegin(), needle.cend(), haystack.cbegin());
}

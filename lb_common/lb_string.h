#pragma once

#include <istream>

#include <streambuf>
#include <string_view>

#include <algorithm>
#include <cctype>
#include <locale>
#include <string>
#include <string_view>
#include <vector>

inline void string_split(std::vector<std::string> & out, const std::string & haystack, char needle) {
    out.clear();
    size_t segment_begin = 0;
    while(true) {
        size_t needle_position = haystack.find(needle, segment_begin);

        if(std::string::npos == needle_position) {
            out.emplace_back(haystack.substr(segment_begin));
            return;
        } else {
            out.emplace_back(haystack.substr(segment_begin, needle_position - segment_begin));
            segment_begin = needle_position + 1;
        }
    }
}

inline std::vector<std::string> string_split(const std::string & haystack, char needle) {
    std::vector<std::string> ret;
    string_split(ret, haystack, needle);
    return ret;
}

// container overload
template <class Container>
inline void string_split(std::vector<std::string> & out, const std::string & haystack, const Container & needles) {
    out.clear();
    static_assert(std::is_same<typename Container::value_type, char>::value || std::is_same<typename Container::value_type, const char>::value);
    size_t segment_begin = 0;
    while(true) {

        size_t needle_position = std::numeric_limits<size_t>::max();
        for(const char needle: needles) {
            needle_position = std::min<size_t>(needle_position, haystack.find(needle, segment_begin));
        }

        if(std::numeric_limits<size_t>::max() == needle_position) {
            out.emplace_back(haystack.substr(segment_begin));
            return;
        } else {
            out.emplace_back(haystack.substr(segment_begin, needle_position - segment_begin));
            segment_begin = needle_position + 1;
        }
    }
}
template <class Container>
inline std::vector<std::string> string_split(const std::string & haystack, const Container & needles) {
    std::vector<std::string> ret;
    string_split(ret, haystack, needles);
    return ret;
}

inline std::string string_join(const std::vector<std::string> & segments, const std::string & joiner) {
    if(segments.empty()) {
        return "";
    }

    std::string result = segments.front();

    std::vector<std::string>::const_iterator segment_iterator = segments.begin() + 1;

    while(segments.cend() != segment_iterator) {
        result += joiner;
        result += *segment_iterator;
        ++segment_iterator;
    }

    return result;
}

inline void string_to_lower(std::string & string) {
    for(char & c: string) {
        c = static_cast<char>(std::tolower(static_cast<int>(c)));
    }
}

inline void string_to_upper(std::string & string) {
    for(char & c: string) {
        c = static_cast<char>(std::toupper(static_cast<int>(c)));
    }
}

inline void string_strip(std::string_view & string) {
    while(false == string.empty() && std::isspace(static_cast<int>(string.front()))) {
        string.remove_prefix(1);
    }
    while(false == string.empty() && std::isspace(static_cast<int>(string.back()))) {
        string.remove_suffix(1);
    }
}

inline void string_strip(std::string & string) {
    while(false == string.empty() && std::isspace(static_cast<int>(string.front()))) {
        string.erase(string.begin());
    }
    while(false == string.empty() && std::isspace(static_cast<int>(string.back()))) {
        string.pop_back();
    }
}

inline std::string string_stripped(const std::string & string) {
    std::string::const_iterator first_non_whitespace = std::find_if(string.cbegin(), string.cend(), 
        [](const char c) -> bool { return 0 == std::isspace(static_cast<int>(c)); }
    );

    if(string.cend() == first_non_whitespace) {
        return "";
    }

    std::string::const_reverse_iterator last_non_whitespace_r = std::find_if(string.crbegin(), string.crend(), 
        [](const char c) -> bool { return 0 == std::isspace(static_cast<int>(c)); }
    );
    std::string::const_iterator non_whitespace_end = last_non_whitespace_r.base();

    return std::string(first_non_whitespace, non_whitespace_end);
}

inline void string_replace_all(std::string & haystack, const std::string & find, const std::string & replace) {
    size_t needle_location = haystack.find(find);

    while(std::string::npos != needle_location) {
        haystack.replace(needle_location, find.size(), replace);
        needle_location = haystack.find(find, needle_location + 1);
    }
}

// templated version of my_equal so it could work with both char and wchar_t
template<typename charT>
struct case_insensitive_equal {
    case_insensitive_equal( const std::locale& loc ) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2) {
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

// Case insensitive lexicographical compare, inspired by the 
// idea (but not implementation of) boost::ilexicographical_compare
inline bool ilexicographical_compare(const std::string & s1, const std::string & s2, const std::locale & locale = std::locale()) {
    std::string::const_iterator it1 = s1.cbegin();
    std::string::const_iterator it2 = s2.cbegin();

    while(true) {
        if(it1 == s1.cend() && it2 == s2.cend()) {
            return false;
        }
        if(it1 == s1.cend() && it2 != s2.cend()) {
            return true;
        }
        if(it1 != s1.cend() && it2 == s2.cend()) {
            return false;
        }

        char c1 = std::tolower(*it1, locale);
        char c2 = std::tolower(*it2, locale);

        if(c1 != c2) {
            return c1 < c2;
        }

        it1++;
        it2++;
    }
}

// find substring (case insensitive)
template<typename CharT>
inline size_t string_ifind( const std::basic_string<CharT>& haystack, const std::basic_string<CharT>& needle, size_t pos = 0, const std::locale& loc = std::locale() )
{
    typename std::basic_string<CharT>::const_iterator it = std::search(haystack.begin() + pos, haystack.end(), 
        needle.begin(), needle.end(), case_insensitive_equal<typename std::basic_string<CharT>::value_type>(loc) );
    if ( it != haystack.end() ) {
        return std::distance(haystack.begin(), it);
    } else {
        return std::string::npos; // not found
    }
}

template <class CharT>
inline void string_ireplace_all(std::basic_string<CharT> & haystack, const std::basic_string<CharT> & search, const std::basic_string<CharT> & replace)  {
    size_t pos = 0;
    while ((pos = string_ifind(haystack, search, pos)) != std::string::npos) {
        haystack.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}

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

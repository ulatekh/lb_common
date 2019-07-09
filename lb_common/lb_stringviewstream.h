#pragma once

#include <istream>
#include <streambuf>

struct stringviewbuf: std::streambuf {
    stringviewbuf(const std::string_view & s) {
        char* p(const_cast<char*>(s.data()));
        this->setg(p, p, p + s.size());
    }
};
struct istringviewstream: virtual stringviewbuf, std::istream {
    istringviewstream(const std::string_view & s)
        : stringviewbuf(s)
        , std::istream(static_cast<std::streambuf*>(this)) {
    }
};

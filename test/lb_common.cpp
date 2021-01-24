#include "../lb_common/lb_string.h"

#include <cassert>

#include <iostream>

void test_string_split() {
    {
        std::string input = "a,bcd,ef";
        std::vector<std::string> expected = {"a", "bcd", "ef"};
        std::vector<std::string> actual = string_split(input, ',');
        assert(actual == expected);
    }

    {
        std::string input = "a,bcd,ef";
        std::vector<std::string> expected = {"a", "bcd", "ef"};
        std::vector<char> separators = {',', ';'};
        std::vector<std::string> actual = string_split(input, separators);

        assert(actual == expected);
    }
}

void test_string_strip() {
    {
        std::string input = " abc\t";
        std::string expected = "abc";
        std::string actual = string_stripped(input);
        assert(actual == expected);
    }

    {
        std::string input = " abc\t";
        std::string expected = "abc";
        string_strip(input);
        assert(input == expected);
    }

    {
        std::string_view input = " abc\t";
        std::string_view expected = "abc";
        string_strip(input);
        assert(input == expected);
    }
}

int main() {
    test_string_split();
    test_string_strip();
}
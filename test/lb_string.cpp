#include "../lb_common/lb_string.h"

#include <cassert>

void test_string_split() {
    { // single
        std::string input = "a,bcd,ef";
        std::vector<std::string> expected = {"a", "bcd", "ef"};
        std::vector<std::string> actual = string_split(input, ',');
        assert(actual == expected);
    }

    { // single inplace
        std::string input = "a,bcd,ef";
        std::vector<std::string> expected = {"a", "bcd", "ef"};
        std::vector<std::string> actual;
        string_split(actual, input, ',');
        assert(actual == expected);
    }

    { // multiple
        std::string input = "a,bcd,ef";
        std::vector<std::string> expected = {"a", "bcd", "ef"};
        std::vector<char> separators = {',', ';'};
        std::vector<std::string> actual = string_split(input, separators);

        assert(actual == expected);
    }

    { // multiple inplace
        std::string input = "a,bcd,ef";
        std::vector<std::string> expected = {"a", "bcd", "ef"};
        std::vector<char> separators = {',', ';'};
        std::vector<std::string> actual;
        string_split(actual, input, separators);

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

void test_ilexicographical_compare() {
    assert(false == ilexicographical_compare("a", "a"));

    assert(true == ilexicographical_compare("a", "b"));
    assert(false == ilexicographical_compare("b", "a"));

    assert(false == ilexicographical_compare("ab", "a"));
    assert(true == ilexicographical_compare("a", "ab"));

    assert(true == ilexicographical_compare("ab", "ac"));
    assert(false == ilexicographical_compare("ac", "ab"));

    // case insensitivity:
    assert(false == ilexicographical_compare("a", "A"));
    assert(false == ilexicographical_compare("A", "a"));

    assert(true == ilexicographical_compare("a", "B"));
    assert(true == ilexicographical_compare("A", "b"));

    // long:
    assert(false == ilexicographical_compare("housekeeper", "House"));
    assert(true == ilexicographical_compare("house", "Housekeeper"));
}

int main() {
    test_string_split();
    test_string_strip();
    test_ilexicographical_compare();
}
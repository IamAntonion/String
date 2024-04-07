#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>

#include "String.h"

bool lexicograp(const char* iter_begin1, const char* iter_last1, const char* iter_begin2, const char* iter_last2) {
    auto iter1 = iter_last1;
    auto iter2 = iter_last2;

    for (; (iter1 != iter_begin1 - 1) && (iter2 != iter_begin2 - 1); --iter1, --iter2) {
        if (*iter1 > *iter2) return true;
        if (*iter1 < *iter2) return false;
    }

    return (iter1 == iter_begin1) && (iter2 != iter_begin2); 
}

void GetReverseLexWord(std::vector<String>& strings) {
    if (strings.empty()) return;
    std::sort(strings.rbegin(), strings.rend(), [](const String& lhs, const String& rhs){
        const char* low_lhs = lhs.LowerCase();
        const char* low_rhs = rhs.LowerCase();
        size_t size_lhs = lhs.Size() - 1;
        size_t size_rhs = rhs.Size() - 1;

        return lexicograp(low_lhs, low_lhs + size_lhs, low_rhs, low_rhs + size_rhs);
    });
}

String operator+(const String& first_str, const String& second_str) {
    String result(first_str);
    result += second_str;
    return result;
}

String operator+(const char* data, const String& str) {
    return String(data) + str;
}

String operator+(const String& str, const char* data) {
    return str + String(data);
}

void TestCopyConstructor() {
    {
        String first("aaa\0");
        String second = first;
        const char* first_data = first.GetData();
        const char* second_data = second.GetData();
        for (;*first_data != '\0'; ++first_data, ++second_data) {
            assert(*first_data == *second_data);
        }
    }

    std::cerr << "Copy constructor test: success" << std::endl;
}

void TestEmpty() {
    {
        String first;

        assert(first.Empty());

        String second("123\0");
        first = second;

        assert(!first.Empty());
        assert(!second.Empty());
    }
    std::cerr << "Empty test: success" << std::endl;
}

void TestMoveSemantics() {
    {
        String first("aaa\0");
        String second(std::move(first));

        assert(first.Empty());
        assert(!second.Empty());
    }
    std::cerr << "Move semantics test: success" << std::endl;
}

void TestLower() {
    {
        String first("Bac\0");
        char* word = first.LowerCase();
        std::string str = "bac\0";
        for (const auto& s : str) {
            assert(*word == s);
            ++word;
        }
    }
    std::cerr << "Lower case test: success" << std::endl;
}

void TestAddClassicString() {
    {
        String first("123\0");
        String second("456\0");
        first += second;
        std::string str = first.GetData();
        assert(str == "123456\0");
    }
    {
        std::string str = "Hello world!\0";
        String cont(str.c_str());
        std::string add = " Hola amigo!\0";
        cont = cont + add.c_str();
        std::string result = cont.GetData();
        assert(result == "Hello world! Hola amigo!\0");
    }
    std::cerr << "Add class String test: success" << std::endl;
}

void TestReverseLexWords() {
    {
        std::vector<String> first;
        std::vector<std::string> input = {"a\0", "aaa\0", "bbb\0", "ccc\0", "ddd\0", "abe\0", "abc\0", "aba\0", "cba\0", "bba\0", "cbb\0"};
        for (const std::string& str : input) {
            first.push_back(String(str.c_str()));
        }

        GetReverseLexWord(first);

        std::vector<std::string> output = {"a\0", "aaa\0", "aba\0", "bba\0", "cba\0", "bbb\0", "cbb\0",  "abc\0", "ccc\0", "ddd\0", "abe\0"};
        int index = 0;
        for (const String& s : first) {
            assert(s.GetData() == output[index]);
            ++index;
        }
    }
    {
        std::vector<String> second;
        std::vector<std::string> input = {"1\0", "5\0", "23\0", "3\0", "7\0", "2\0", "99\0"};
        for (const std::string& str : input) {
            second.push_back(String(str.c_str()));
        }

        GetReverseLexWord(second);

        std::vector<std::string> output = {"1\0", "2\0", "3\0", "23\0", "5\0", "7\0", "99\0"};
        int index = 0;
        for (const String& s : second) {
            assert(s.GetData() == output[index]);
            ++index;
        }
    }
    std::cerr << "Reverse lexicographic order test: success" << std::endl;
}
void TestSize() {
    {
        String first("123");
        assert(first.Size() == 3);
    }
    std::cerr << "Size test: success" << std::endl;
}

void Tests() {
    TestCopyConstructor();
    TestEmpty();
    TestSize();
    TestMoveSemantics();
    TestLower();
    TestReverseLexWords();
    TestAddClassicString();

    std::cerr << "All tests passed success!" << std::endl;
}

int main() {
    Tests();

    std::vector<String> strings;
    std::string str;

    std::cout << "Enter a words:" << std::endl;

    while (std::cin >> str) {
        strings.push_back(String(str.c_str()));
    }

    GetReverseLexWord(strings);

    std::cout << "Reverse lexicographic word list:" << std::endl;

    for (const String& s : strings) {
        std::cout << s.GetData() << std::endl;
    }

    return 0;
}
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>

#include "String.h"

bool lexicograp(const char* iter_begin1, const char* iter_last1, const char* iter_begin2, const char* iter_last2) {
    auto iter1 = iter_begin1;
    auto iter2 = iter_begin2;

    for (; (iter1 != iter_last1) && (iter2 != iter_last2); ++iter1, ++iter2) {
        if (*iter1 < *iter2) return true;
        if (*iter1 > *iter2) return false;
    }

    return (iter1 == iter_last1) && (iter2 != iter_last2); 
}

void GetReverseLexWord(std::vector<String>& strings) {
    if (strings.empty()) return;
    std::sort(strings.rbegin(), strings.rend(), [](const String& lhs, const String& rhs){
        const char* low_lhs = lhs.LowerCase();
        const char* low_rhs = rhs.LowerCase();
        size_t size_lhs = lhs.Size();
        size_t size_rhs = rhs.Size();

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
        String first("aaa");
        String second = first;
        const char* first_data = first.GetData();
        const char* second_data = second.GetData();
        for (;*first_data != '\0'; ++first_data, ++second_data) {
            assert(*first_data == *second_data);
        }
    }
}

void TestEmpty() {
    {
        String first;

        assert(first.Empty());

        String second("123");
        first = second;

        assert(!first.Empty());
        assert(!second.Empty());
    }
}

void TestMoveConstructor() {
    {
        String first("aaa");
        String second(std::move(first));

        assert(first.Empty());
        assert(!second.Empty());
    }
}

void TestLower() {
    {
        String first("Bac\0");
        char* word = first.LowerCase();
        std::string str = "bac";
        for (const auto& s : str) {
            assert(*word == s);
            ++word;
        }
    }
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
}

void TestReverseLexWords() {
    {
        std::vector<String> first;
        std::vector<std::string> input = {"aaa", "bbb", "ccc", "ddd", "abe", "abc"};
        for (const std::string& str : input) {
            first.push_back(String(str.c_str()));
        }

        GetReverseLexWord(first);

        std::vector<std::string> output = {"ddd", "ccc", "bbb", "abe", "abc", "aaa"};
        int index = 0;
        for (const String& s : first) {
            assert(s.GetData() == output[index]);
            //std::cout << s.GetData() << std::endl; 
            ++index;
        }
    }
    {
        std::vector<String> second;
        std::vector<std::string> input = {"1", "5", "23", "3", "7", "2", "99"};
        for (const std::string& str : input) {
            second.push_back(String(str.c_str()));
        }

        GetReverseLexWord(second);

        std::vector<std::string> output = {"99", "7", "5", "3", "23", "2", "1"};
        int index = 0;
        for (const String& s : second) {
            assert(s.GetData() == output[index]);
            ++index;
        }
    }
}

void Tests() {
    TestCopyConstructor();
    TestEmpty();
    TestMoveConstructor();
    TestLower();
    TestReverseLexWords();
    TestAddClassicString();

    std::cout << "All tests passed success!" << std::endl;
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
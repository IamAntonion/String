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

void GetReverseLexWord(std::vector<str::string_container_for_targem_games>& strings) {
    if (strings.empty()) return;
    std::sort(strings.rbegin(), strings.rend(), [](const str::string_container_for_targem_games& lhs, const str::string_container_for_targem_games& rhs){
        const char* low_lhs = lhs.LowerCase();
        const char* low_rhs = rhs.LowerCase();
        size_t size_lhs = lhs.Size();
        size_t size_rhs = rhs.Size();

        return lexicograp(low_lhs, low_lhs + size_lhs, low_rhs, low_rhs + size_rhs);
    });
}

str::string_container_for_targem_games operator+(const str::string_container_for_targem_games& first_str, const str::string_container_for_targem_games& second_str) {
    str::string_container_for_targem_games result(first_str);
    result += second_str;
    return result;
}

str::string_container_for_targem_games operator+(const char* data, const str::string_container_for_targem_games& str) {
    return str::string_container_for_targem_games(data) + str;
}

str::string_container_for_targem_games operator+(const str::string_container_for_targem_games& str, const char* data) {
    return str + str::string_container_for_targem_games(data);
}

void TestCopyConstructor() {
    {
        str::string_container_for_targem_games first("aaa\0");
        str::string_container_for_targem_games second = first;
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
        str::string_container_for_targem_games first;

        assert(first.Empty());

        str::string_container_for_targem_games second("123\0");
        first = second;

        assert(!first.Empty());
        assert(!second.Empty());
    }
    std::cerr << "Empty test: success" << std::endl;
}

void TestMoveSemantics() {
    {
        str::string_container_for_targem_games first("aaa\0");
        str::string_container_for_targem_games second(std::move(first));

        assert(first.Empty());
        assert(!second.Empty());
    }
    std::cerr << "Move semantics test: success" << std::endl;
}

void TestLower() {
    {
        str::string_container_for_targem_games first("Bac\0");
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
        str::string_container_for_targem_games first("123\0");
        str::string_container_for_targem_games second("456\0");
        first += second;
        std::string str = first.GetData();
        assert(str == "123456\0");
    }
    {
        std::string str = "Hello world!\0";
        str::string_container_for_targem_games cont(str.c_str());
        std::string add = " Hola amigo!\0";
        cont = cont + add.c_str();
        std::string result = cont.GetData();
        assert(result == "Hello world! Hola amigo!\0");
    }
    std::cerr << "Add class String test: success" << std::endl;
}

void TestReverseLexWords() {
    {
        std::vector<str::string_container_for_targem_games> first;
        std::vector<std::string> input = {"a\0", "aaa\0", "bbb\0", "ccc\0", "ddd\0", "abe\0", "abc\0", "aba\0", "cba\0", "bba\0", "cbb\0"};
        for (const std::string& str : input) {
            first.push_back(str::string_container_for_targem_games(str.c_str()));
        }

        GetReverseLexWord(first);

        std::vector<std::string> output = {"a\0", "aaa\0", "aba\0", "bba\0", "cba\0", "bbb\0", "cbb\0",  "abc\0", "ccc\0", "ddd\0", "abe\0"};
        int index = 0;
        for (const str::string_container_for_targem_games& s : first) {
            assert(s.GetData() == output[index]);
            ++index;
        }
    }
    {
        std::vector<str::string_container_for_targem_games> second;
        std::vector<std::string> input = {"1\0", "5\0", "23\0", "13\0", "3\0", "7\0", "2\0", "99\0"};
        for (const std::string& str : input) {
            second.push_back(str::string_container_for_targem_games(str.c_str()));
        }

        GetReverseLexWord(second);

        std::vector<std::string> output = {"1\0", "2\0", "3\0", "13\0", "23\0", "5\0", "7\0", "99\0"};
        int index = 0;
        for (const str::string_container_for_targem_games& s : second) {
            assert(s.GetData() == output[index]);
            ++index;
        }
    }
    std::cerr << "Reverse lexicographic order test: success" << std::endl;
}
void TestSize() {
    {
        str::string_container_for_targem_games first("123");
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

    std::vector<str::string_container_for_targem_games> strings;
    std::string str;

    std::cout << "Enter a words:" << std::endl;

    while (std::cin >> str) {
        strings.push_back(str::string_container_for_targem_games(str.c_str()));
    }

    GetReverseLexWord(strings);

    std::cout << "Reverse lexicographic word list:" << std::endl;

    for (const str::string_container_for_targem_games& s : strings) {
        std::cout << s.GetData() << std::endl;
    }

    return 0;
}
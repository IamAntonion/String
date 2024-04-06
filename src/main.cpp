#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "String.h"

/*
input: 
aaa bbb ccc ddd abe abc

output:
ddd ccc bbb bea abc aaa
*/


String operator+(const String& first_str, const String& second_str) {
    String result(first_str);
    result += second_str;
    return result;
}

String operator+(const char* data, const String& str) {
    return String(data) + str;
}

int main() {
    std::vector<String> strings;
    std::string str;

    std::cout << "Enter a list of string" << std::endl;

    while (std::cin >> str) {
        strings.push_back(String(str.c_str()));
    }

    std::sort(strings.rbegin(), strings.rend(), [](const String& lhs, const String& rhs){
        const char* low_lhs = lhs.LowerCase();
        const char* low_rhs = rhs.LowerCase();
        return strcmp(low_lhs, low_rhs) < 0;
    });

    std::cout << "Revers:" << std::endl;

    for (const String& s : strings) {
        std::cout << s.GetData() << std::endl;
    }

    return 0;
}
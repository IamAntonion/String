#include "String.h"

String::String() : data_(nullptr), size_(0) {}

String::String(const char* data) {
    //size_ = LengthString(data);
    size_ = strlen(data);
    data_ = new char[size_ + 1];

    //CopyString(data_, data);
    strcpy(data_, data);
}

String::String(const String& str) {
    this->size_ = str.size_;
    this->data_ = new char[size_ + 1];
    strcpy(this->data_, str.data_);
    //CopyString(this->data_, str.data_);
}

String::String(String&& str) noexcept : data_(str.data_), size_(str.size_) {
    str.data_ = nullptr;
    str.size_ = 0;
}

String::~String() noexcept{
    if (data_) delete[] data_;
}

String& String::operator=(const String& str) { 
    if (this != &str) {
        if (data_) delete[] data_;
        this->size_ = str.size_;
        this->data_ = new char[size_ + 1];
        //CopyString(this->data_,str.data_);
        strcpy(this->data_, str.data_);
    }
    return *this;
}

String& String::operator+=(const String& other) {
    AddStr(other.data_);
    return *this;
}

bool String::Empty() const{
    return size_ == 0;
}

const char* String::GetData() const {
    return data_;
}

void String::CopyString(char* fillableData, const char* data) {
    char* tmp = fillableData;
    const char* str = data;
    while (*str != '\0') {
        *tmp = *str;
        ++tmp;
        ++str;
    }
    *tmp = '\0';
}

size_t String::LengthString(const char* data) {
    const char* end_data = data;
    while(*end_data) {
        ++end_data;
    }
    return end_data - data;
}

void String::AddStr(const char* data) {
    size_t tmp_size = size_ + LengthString(data);
    char* tmp_data = new char[tmp_size];

    CopyString(tmp_data, data_);
    CopyString(tmp_data + tmp_size, data);

    if (data_) delete[] data_;

    data_ = tmp_data;
    size_ = tmp_size;
}

char* String::LowerCase() const {
    char* lower = new char[size_ + 1];
    for (int i = 0; i != size_; ++i) {
        lower[i] = std::tolower(data_[i]);
    }
    lower[size_ + 1] = '\0';
    return lower;
}
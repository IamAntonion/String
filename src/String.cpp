#include "String.h"

namespace str {
    string_container_for_targem_games::string_container_for_targem_games() : data_(nullptr), size_(0) {}

    string_container_for_targem_games::string_container_for_targem_games(const char* data) {
        size_ = strlen(data);
        data_ = new char[size_];

        strcpy(data_, data);
    }

    string_container_for_targem_games::string_container_for_targem_games(const string_container_for_targem_games& str) {
        this->size_ = str.size_;
        this->data_ = new char[size_];

        strcpy(this->data_, str.data_);
    }

    string_container_for_targem_games::string_container_for_targem_games(string_container_for_targem_games&& str) noexcept : data_(str.data_), size_(str.size_) {
        str.data_ = nullptr;
        str.size_ = 0;
    }

    string_container_for_targem_games::~string_container_for_targem_games() noexcept{
        if (data_) delete[] data_;
    }

    string_container_for_targem_games& string_container_for_targem_games::operator=(const string_container_for_targem_games& str) { 
        if (this != &str) {
            if (data_) delete[] data_;
            this->size_ = str.size_;
            this->data_ = new char[size_];

            strcpy(this->data_, str.data_);
        }
        return *this;
    }

    string_container_for_targem_games& string_container_for_targem_games::operator=(string_container_for_targem_games&& str) { 
        if (this != &str) {
            if (data_) delete[] data_;
            this->size_ = str.size_;
            this->data_ = new char[size_];

            strcpy(this->data_, str.data_);

            str.data_ = nullptr;
            str.size_ = 0;
        }
        return *this;
    }

    string_container_for_targem_games& string_container_for_targem_games::operator+=(const string_container_for_targem_games& str) {
        AddStr(str.data_);
        return *this;
    }

    bool string_container_for_targem_games::Empty() const{
        return size_ == 0;
    }

    const char* string_container_for_targem_games::GetData() const {
        return data_;
    }

    void string_container_for_targem_games::AddStr(const char* data) {
        size_t tmp_size = size_ + strlen(data);
        char* tmp_data = new char[tmp_size];

        strcpy(tmp_data, data_);
        strcpy(tmp_data + strlen(data), data);

        if (data_) delete[] data_;

        data_ = tmp_data;
        size_ = tmp_size;
    }

    char* string_container_for_targem_games::LowerCase() const {
        char* lower = new char[size_];
        for (int i = 0; i != size_; ++i) {
            lower[i] = std::tolower(data_[i]);
        }
        lower[size_] = '\0';
        return lower;
    }

    size_t string_container_for_targem_games::Size() const {
        return size_;
    }
}
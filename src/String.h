#include <stddef.h>
#include <cstring>
#include <cctype>
#include <iostream>

class String {
public:
    String();                                   // The constructor creates a String with null data and size 0
    explicit String(const char* data);          // The constructor creates a string with the input parameter data 
    String(const String& str);                  // The constructor creates a string with the other String parameters
    String(String&& str) noexcept;              // Move semantics
    ~String() noexcept;                         // The destructor frees data 

    String& operator=(const String& str);
    String& operator+=(const String& other);

    bool Empty() const;                         // Checking for emptiness
    const char* GetData() const;                // Getting data into a classic string
    size_t Size() const;                        // Get size of data String

    char* LowerCase() const;                    // Convert from upper case to lower case without changing the data
private:
    char* data_;                                // Data pointer
    size_t size_;                               // Size data

    void CopyString(char* fillableData,         // Alternative to strcpy
                    const char* data);
    size_t LengthString(const char* data);      // Alternative to strlen

    void AddStr(const char* str);               // Add new data to cucurrent data
};
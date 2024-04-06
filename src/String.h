#include <stddef.h>
#include <cstring>
#include <cctype>

class String {
public:
    String();
    explicit String(const char* data);
    String(const String& str);
    String(String&& str) noexcept;
    ~String() noexcept;

    String& operator=(const String& str);
    String& operator+=(const String& other);

    bool Empty() const;
    const char* GetData() const;
    size_t Size() const;

    char* LowerCase() const;
private:
    char* data_;
    size_t size_;

    void CopyString(char* fillableData, const char* data);
    size_t LengthString(const char* data);

    void AddStr(const char* str);
};
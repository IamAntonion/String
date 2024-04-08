#include <stddef.h>
#include <cstring>
#include <cctype>

namespace str {
    class string_container_for_targem_games {
    public:
        string_container_for_targem_games();                                                    // The constructor creates a String with null data and size 0
        explicit string_container_for_targem_games(const char* data);                           // The constructor creates a string with the input parameter data 
        string_container_for_targem_games(const string_container_for_targem_games& str);        // The constructor creates a string with the other String parameters (Copy)
        string_container_for_targem_games(string_container_for_targem_games&& str) noexcept;    // Move semantics
        ~string_container_for_targem_games() noexcept;                                          // The destructor frees data 

        string_container_for_targem_games& operator=(const string_container_for_targem_games& str);
        string_container_for_targem_games& operator=(string_container_for_targem_games&& str);
        string_container_for_targem_games& operator+=(const string_container_for_targem_games& str);

        bool Empty() const;                             // Checking for emptiness
        const char* GetData() const;                    // Getting data into a classic string
        size_t Size() const;                            // Get size of data String

        char* LowerCase() const;                        // Convert from upper case to lower case without changing the data
    private:
        char* data_;                                    // Data pointer
        size_t size_;                                   // Size data

        void AddStr(const char* str);                   // Add new data to cucurrent data
    };
}
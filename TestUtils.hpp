#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <string>

// Helper function to check if string contains substring
inline bool ContainsSubstring(const std::string& str, const std::string& substr) {
    return str.find(substr) != std::string::npos;
}

#endif // TEST_UTILS_HPP

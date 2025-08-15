#include "include/utility.h"
#include <climits>
#include <cstdlib>
#include <cctype>

int nu_function(int prime, int coefficient) {
    if (coefficient == 0) return INT_MAX;
    coefficient = abs(coefficient);
    int answer = 0;
    while (coefficient % prime == 0) {
        coefficient /= prime;
        answer++;
    }
    return answer;
}

int gcd_function(int a, int b) {
    return (b == 0) ? abs(a) : gcd_function(b, a % b);
}

bool is_integer(const std::string& str) {
    if (str.empty()) return false;
    size_t start = 0;
    while (start < str.size() && str[start] == ' ') start++;
    if (start == str.size()) return false;
    if (str[start] == '-' || str[start] == '+') ++start;
    for (size_t i = start; i < str.size(); ++i) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

bool is_prime(int number) {
    if (number < 2) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    for (int i = 3; i*i <= number; i += 2) {
        if (number % i == 0) return false;
    }
    return true;
}


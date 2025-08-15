#include "polynomial.h"
#include "utility.h"
#include "config.h"
#include <iostream>

void take_inputs() {
    std::string temp;
    while (true) {
        std::cout << "Enter polygon target prime:\n";
        std::getline(std::cin, temp);
        if (is_integer(temp) && is_prime(std::stoi(temp))) {
            p = std::stoi(temp);
            break;
        } else {
            std::cout << "Invalid input! Attempt aborted.\n\n";
        }
    }

    while (true) {
        std::cout << "Enter polynomial degree:\n";
        std::getline(std::cin, temp);
        if (is_integer(temp) && std::stoi(temp) >= 0) {
            n = std::stoi(temp);
            break;
        } else {
            std::cout << "Invalid input! Attempt aborted.\n\n";
        }
    }

    polynomial_coefficients.resize(n + 1);
    for (int i = n; i >= 0; --i) {
        while (true) {
            std::cout << "Enter coefficient for x^" << i << ":\n";
            std::getline(std::cin, temp);
            if (is_integer(temp)) {
                polynomial_coefficients[i] = std::stoi(temp);
                break;
            } else {
                std::cout << "Invalid input! Attempt aborted.\n\n";
            }
        }
    }
}

void output_given_polynomial() {
    std::cout << "\nf(x) = ";
    for (int i = n; i >= 0; --i) {
        std::cout << polynomial_coefficients[i];
        if (i != 0) std::cout << "x^" << i << " + ";
    }
    std::cout << '\n';
}

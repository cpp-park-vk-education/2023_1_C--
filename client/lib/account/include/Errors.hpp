#pragma once
#include <stdexcept>

class Error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class FormError : public Error {
public:
    FormError(const std::string& what) : Error{what} {}
};

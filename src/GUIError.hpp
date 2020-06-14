#pragma once

#include <stdexcept>

namespace GUI
{

    class Error : public std::runtime_error
    {
    public:
        Error(const char* what_arg) : std::runtime_error("GUI: " + std::string(what_arg)) {}
        Error(const std::string& what_arg) : std::runtime_error("GUI: " + what_arg) {}
    };
}
//
// Created by araulo22 on 4/18/2021.
//

#include "MovieException.h"

MovieException::MovieException(std::string message):message{message} {
    error = "Movie Error: " + message;
}

const char *MovieException::what() const noexcept {
    return error.c_str();
}


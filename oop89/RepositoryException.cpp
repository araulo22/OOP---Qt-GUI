//
// Created by araulo22 on 4/18/2021.
//

#include "RepositoryException.h"

RepositoryException::RepositoryException(std::string message):message{message} {
    error = "Repository Error: " + message;
}

const char *RepositoryException::what() const noexcept {
    return error.c_str();
}


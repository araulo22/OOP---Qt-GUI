//
// Created by araulo22 on 4/18/2021.
//

#ifndef A45_ARAULO22_REPOSITORYEXCEPTION_H
#define A45_ARAULO22_REPOSITORYEXCEPTION_H

#endif //A45_ARAULO22_REPOSITORYEXCEPTION_H
#include <string>
#pragma once

class RepositoryException: public std::exception {
private:
    std::string message;
    std::string error;
public:
    RepositoryException(std::string message = "");
    const char* what() const noexcept;
};
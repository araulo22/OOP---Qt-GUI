//
// Created by araulo22 on 4/18/2021.
//

#ifndef A45_ARAULO22_CUSTOMEXCEPTION_H
#define A45_ARAULO22_CUSTOMEXCEPTION_H

#endif //A45_ARAULO22_CUSTOMEXCEPTION_H
#include <string>

class MovieException: public std::exception {
private:
    std::string message;
    std::string error;
public:
    MovieException(std::string message = "");
    const char* what() const noexcept;
};
//
// Created by araulo22 on 4/18/2021.
//

#include "MovieValidator.h"
#include <ctime>

void MovieValidator::validate(const Movie &movie) {
    std::string title = movie.getTitle();
    std::string genre = movie.getGenre();
    int likes = movie.getLikes();
    int release = movie.getYear();
    std::string trailer = movie.getTrailer();
    std::string errors;

    time_t t = time(NULL);
    tm* timePointer = localtime(&t);
    int currentYear = timePointer->tm_year + 1900;

    if(title.size() < 2)
        errors += "[Invalid title]";
    if(likes < 0)
        errors += "[Invalid likes]";
    if(release < 1900 || release > currentYear)
        errors += "[Invalid year]";
    if(genre.size() < 2)
        errors += "[Invalid genre]";
    if(!errors.empty())
        throw MovieException(errors);
}

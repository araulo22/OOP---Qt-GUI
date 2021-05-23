//
// Created by araulo22 on 4/18/2021.
//

#include "HTMLRepository.h"
#pragma once

void HTMLRepository::writeUserFile(std::vector<Movie> movies) {
    std::ofstream output(userFileName, std::ofstream::out | std::ofstream::trunc);
    output << "<!DOCTYPE html>\n<html><head><title>Movie Watchlist</title></head><body>\n";
    output << "<table border=\"1\">\n";
    output << "<tr><td>Title</td><td>Genre</td><td>Release Year</td><td>Likes</td><td>Trailer</td></tr>\n";
    for(const Movie &movie : movies) {
        output << "<tr><td>" << movie.getTitle() << "</td>"
                   << "<td>" << movie.getGenre() << "</td>"
                   << "<td>" << movie.getYear() << "</td>"
                   << "<td>" << movie.getLikes() << "</td>"
                   << "<td><a href=\"" << movie.getTrailer() << "\">"<<movie.getTrailer()<<"</a></td>" << '\n';
    }
    output << "</table></body></html>";
    output.close();
}

int HTMLRepository::addMovieToWatchlist(const Movie &movieToAdd) {
    FileRepository::addMovieToWatchlist(movieToAdd);
    this->writeUserFile(userWatchList);
    return 1;
}

int HTMLRepository::addMovieToWatchListByTitle(const std::string &tempMovie) {
    FileRepository::addMovieToWatchListByTitle(tempMovie);
    this->writeUserFile(userWatchList);
    return 1;
}

int HTMLRepository::deleteMovieFromWatchList(const std::string &title, bool liked) {
    FileRepository::deleteMovieFromWatchList(title, liked);
    this->writeUserFile(userWatchList);
    return 1;
}

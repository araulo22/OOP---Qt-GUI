//
// Created by araulo22 on 4/18/2021.
//

#include "CSVRepository.h"

void CSVRepository::writeUserFile(std::vector<Movie> movies) {
    std::ofstream output(userFileName, std::ofstream::out | std::ofstream::trunc);
    output << "Title, Genre, Release Year, Likes, Trailer";
    if(movies.empty())
        return;
    for(const Movie& movie : movies)
    {
        output << movie.getTitle() << ", "
        << movie.getGenre() << ", "
        << movie.getYear() << ", "
        << movie.getLikes() << ", "
        << movie.getTrailer() << '\n';
    }
    output.close();
}

int CSVRepository::addMovieToWatchlist(const Movie &movieToAdd) {
    FileRepository::addMovieToWatchlist(movieToAdd);
    this->writeUserFile(userWatchList);
    return 1;
}

int CSVRepository::addMovieToWatchListByTitle(const std::string &tempMovie) {
    FileRepository::addMovieToWatchListByTitle(tempMovie);
    this->writeUserFile(userWatchList);
    return 1;
}

int CSVRepository::deleteMovieFromWatchList(const std::string &title, bool liked) {
    FileRepository::deleteMovieFromWatchList(title, liked);
    this->writeUserFile(userWatchList);
    return 1;
}

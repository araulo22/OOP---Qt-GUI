//
// Created by araul on 28.03.2021.
//

#ifndef A45_ARAULO22_REPOSITORY_H
#define A45_ARAULO22_REPOSITORY_H
#endif //A45_ARAULO22_REPOSITORY_H
#pragma once
#include "Movie.h"
#include <vector>
#include <algorithm>


class Repository
{
protected:
    std::vector<Movie> movieList;
    std::vector<Movie> userWatchList;
    std::string repoType;
public:
    Repository();

    virtual int addMovie(const Movie& movieToAdd);
    virtual int deleteMovie(const Movie& movieToDelete);
    virtual int updateMovie(const Movie& ToUpdateWith);
    virtual std::vector<Movie> getMoviesByGenre(const std::string& genreGiven = "");
    virtual std::vector<Movie> getAllMovies();
    virtual std::vector<Movie> getAllWatchListMovies();
    virtual Movie getMovieAtPosition(int positionOfMovie);
    virtual int getNumberOfMovies();
    virtual int addMovieToWatchlist(const Movie& movieToAdd);
    virtual int addMovieToWatchListByTitle(const std::string& tempMovie);
    virtual int getNumberOfMoviesWatchList();
    virtual int deleteMovieFromWatchList(const std::string& title, bool liked);
    virtual void addLike(const std::string& title);
    virtual std::string getRepoType();
    virtual std::string getUserFileName();
    virtual std::string getMainFileName();
    virtual Movie getMovieByTitle(const std::string& title) {};
    virtual void changeUserFileName(const std::string& name) {};
    virtual void changeMainFileName(const std::string& name) {};
    virtual void openFile();
};

//
// Created by araul on 28.03.2021.
//

#include "Repository.h"
#include <iostream>
#include <fstream>

//Repository constructor
Repository::Repository()
{
    std::vector<Movie>{};
    repoType = "MEMORY";
}

//Add given movie to list
int Repository::addMovie(const Movie& movieToAdd)
{
    auto movie = std::find(movieList.begin(), movieList.end(), movieToAdd);
    if (movie != movieList.end() && !movieList.empty())
        return -1;
    movieList.push_back(movieToAdd);
    return 1;
}

//Delete a movie from the movieList
int Repository::deleteMovie(const Movie& movieToDelete)
{
    auto movie = std::find(movieList.begin(), movieList.end(), movieToDelete);
    if (movie == movieList.end())
        return -1;
    movieList.erase(movie);
    return 1;
}

//Update a movie from the movieList
int Repository::updateMovie(const Movie& movieToUpdateWith)
{
    auto movie = std::find(movieList.begin(), movieList.end(), movieToUpdateWith);
    if (movie == movieList.end())
        return -1;
    *movie = movieToUpdateWith;
    return 1;
}

//Get all the movies with a given genre
std::vector<Movie> Repository::getMoviesByGenre(const std::string& genreGiven)
{
    std::vector<Movie> moviesWithGenre;
    if (genreGiven.empty())
        return movieList;
    std::copy_if(movieList.begin(), movieList.end(), std::back_inserter(moviesWithGenre), [&genreGiven](const Movie& movie) {return movie.getGenre() == genreGiven; });
    return moviesWithGenre;
}

//Get all the movies
std::vector<Movie> Repository::getAllMovies()
{
    return movieList;
}

//Get all the movies in the watch list
std::vector<Movie> Repository::getAllWatchListMovies()
{
    return userWatchList;
}

//Add a certain movie to the watch list
int Repository::addMovieToWatchlist(const Movie& movieToAdd)
{
    auto movie = std::find(userWatchList.begin(), userWatchList.end(), movieToAdd);
    if (movie != userWatchList.end())
        return -1;
    userWatchList.push_back(movieToAdd);
    return 1;
}

//Add a certain movie to the watch list by the title
int Repository::addMovieToWatchListByTitle(const std::string& titleOfTheMovieToAdd)
{
    auto movie = std::find_if(movieList.begin(), movieList.end(), [&titleOfTheMovieToAdd](const Movie& tempMovie) {return tempMovie.getTitle() == titleOfTheMovieToAdd;});
    if (movie == movieList.end())
        return -1;
    userWatchList.push_back(*movie);
    return 1;
}

//Get the number of movies in the watch list
int Repository::getNumberOfMoviesWatchList()
{
    return userWatchList.size();
}

//Delete movie from user watch list and add a like if user liked it
int Repository::deleteMovieFromWatchList(const std::string &title, bool liked)
{
    auto movie = std::find_if(userWatchList.begin(), userWatchList.end(), [&title](const Movie& tempMovie) {return tempMovie.getTitle() == title;});
    if(movie == userWatchList.end())
        return -1;
    if(liked)
        addLike(title);
    userWatchList.erase(movie);
    return 1;
}

void Repository::addLike(const std::string &title) {
    auto movie = std::find_if(movieList.begin(), movieList.end(), [&title](const Movie& tempMovie) {return tempMovie.getTitle() == title;});
    movie->setLikes(movie->getLikes() + 1);
}

int Repository::getNumberOfMovies() {
    return movieList.size();
}

Movie Repository::getMovieAtPosition(int positionOfMovie) {
    if (positionOfMovie < 0 || positionOfMovie >= movieList.size())
        throw std::runtime_error("Invalid position");
    return movieList[positionOfMovie];
}

std::string Repository::getUserFileName() {
    return "In Memory";
}

std::string Repository::getMainFileName() {
    return "In Memory";
}

std::string Repository::getRepoType() {
    return repoType;
}

void Repository::openFile() {

}

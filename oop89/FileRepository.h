//
// Created by araulo22 on 4/18/2021.
//

#ifndef A45_ARAULO22_FILEREPOSITORY_H
#define A45_ARAULO22_FILEREPOSITORY_H

#endif //A45_ARAULO22_FILEREPOSITORY_H

#pragma once
#include "Repository.h"
#include "RepositoryException.h"
#include <fstream>
#include <windows.h>

class FileRepository: public Repository {
protected:
    std::string userFileName;
    std::string mainFileName;

public:
    FileRepository(const std::string& fileName = "");
    std::vector<Movie> loadFile();
    std::vector<Movie> loadUserFile();
    void writeFile(std::vector<Movie> movies);
    virtual void writeUserFile(std::vector<Movie> movies);
    int addMovie(const Movie& movieToAdd) override;
    int deleteMovie(const Movie& movieToDelete) override;
    int updateMovie(const Movie& ToUpdateWith) override;
    void changeUserFileName(const std::string& name) override;
    void changeMainFileName(const std::string& name) override;
    std::string getUserFileName() override;
    std::string getMainFileName() override;
    std::vector<Movie> getMoviesByGenre(const std::string& genreGiven = "");
    std::vector<Movie> getAllMovies() override;
    std::vector<Movie> getAllWatchListMovies() override;
    Movie getMovieAtPosition(int positionOfMovie) override;
    Movie getMovieByTitle(const std::string& title) override;
    int getNumberOfMovies() override;
    virtual int addMovieToWatchlist(const Movie& movieToAdd) override;
    virtual int addMovieToWatchListByTitle(const std::string& tempMovie) override;
    int getNumberOfMoviesWatchList() override;
    virtual int deleteMovieFromWatchList(const std::string& title, bool liked) override;
    void addLike(const std::string& title) override;
    virtual void openFile();
};

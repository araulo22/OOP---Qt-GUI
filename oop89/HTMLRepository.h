//
// Created by araulo22 on 4/18/2021.
//

#ifndef A45_ARAULO22_HTMLREPOSITORY_H
#define A45_ARAULO22_HTMLREPOSITORY_H
#pragma once
#include "FileRepository.h"
#include <fstream>

class HTMLRepository: public FileRepository {
public:
    HTMLRepository(std::string fileName="user.csv", std::string mainFile = "data.txt") {this->userFileName = fileName; this->mainFileName = mainFile; this->repoType = "HTML";};
    void writeUserFile(std::vector<Movie> movies) override;
    int addMovieToWatchlist(const Movie& movieToAdd) override;
    int addMovieToWatchListByTitle(const std::string& tempMovie) override;
    int deleteMovieFromWatchList(const std::string& title, bool liked) override;
};

#endif //A45_ARAULO22_HTMLREPOSITORY_H

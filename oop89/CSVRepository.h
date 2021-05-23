//
// Created by araulo22 on 4/18/2021.
//

#ifndef A45_ARAULO22_CSVREPOSITORY_H
#define A45_ARAULO22_CSVREPOSITORY_H
#pragma once
#include "FileRepository.h"
#include <fstream>

class CSVRepository: public FileRepository {
public:
    CSVRepository(std::string fileName="user.csv", std::string mainFile = "data.txt") {this->userFileName = fileName; this->mainFileName = mainFile; this->repoType = "CSV";};
    void writeUserFile(std::vector<Movie> movies) override;
    int addMovieToWatchlist(const Movie& movieToAdd) override;
    int addMovieToWatchListByTitle(const std::string& tempMovie) override;
    int deleteMovieFromWatchList(const std::string& title, bool liked) override;
};

#endif //A45_ARAULO22_CSVREPOSITORY_H

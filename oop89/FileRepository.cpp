//
// Created by araulo22 on 4/18/2021.
//

#include "FileRepository.h"

FileRepository::FileRepository(const std::string &fileName) {
    mainFileName = fileName;
    userFileName = "user.txt";
    repoType = "txt";
}

std::vector<Movie> FileRepository::loadFile() {
    std::vector<Movie> movies = {};
    Movie temp;
    if(mainFileName.empty())
        changeMainFileName("data.txt");
    try {
        std::ifstream fin(mainFileName);
        while(fin >> temp) {
            if(std::find(movies.begin(), movies.end(), temp) == movies.end())
                movies.push_back(temp);
        }
        fin.close();
        return movies;
    }
    catch (std::exception & e) {}
}

void FileRepository::writeFile(std::vector<Movie> movies) {
    std::ofstream fout(mainFileName, std::ofstream::out | std::ofstream::trunc);
    for(const Movie &temp : movies)
        fout << temp << '\n';
    fout.close();
}

void FileRepository::writeUserFile(std::vector<Movie> movies) {
    std::ofstream fout(userFileName, std::ofstream::out | std::ofstream::trunc);
    for(const Movie &temp : movies)
        fout << temp << '\n';
    fout.close();
}

int FileRepository::addMovie(const Movie &movieToAdd) {
    std::vector<Movie> movies;
    movies = loadFile();
    auto temp = std::find(movies.begin(), movies.end(), movieToAdd);
    if(temp != movies.end() && movies.size() != 0)
        throw RepositoryException(std::string("[Movie Already In List]"));
    movies.push_back(movieToAdd);
    writeFile(movies);
    return 1;
}

int FileRepository::deleteMovie(const Movie &movieToDelete) {
    std::vector<Movie> movies;
    movies = loadFile();
    auto temp = std::find(movies.begin(), movies.end(), movieToDelete);
    if(temp == movies.end())
        throw RepositoryException(std::string("[Movie Not In List]"));
    movies.erase(temp);
    writeFile(movies);
    return 1;
}

int FileRepository::updateMovie(const Movie &ToUpdateWith) {
    std::vector<Movie> movies;
    movies = loadFile();
    auto temp = std::find(movies.begin(), movies.end(), ToUpdateWith);
    if(temp == movies.end())
        throw RepositoryException(std::string("[Movie Not In List]"));
    *temp = ToUpdateWith;
    writeFile(movies);
    return 1;
}

void FileRepository::changeUserFileName(const std::string &name) {
    if(name.empty())
        throw RepositoryException(std::string("[Invalid file name]"));
    userFileName = name;
}

void FileRepository::changeMainFileName(const std::string &name) {
    if(name.empty())
        throw RepositoryException(std::string("[Invalid file name]"));
    mainFileName = name;
}

std::vector<Movie> FileRepository::getAllMovies() {
    std::vector<Movie> movies = loadFile();
    return movies;
}

std::vector<Movie> FileRepository::getMoviesByGenre(const std::string &genreGiven) {
    std::vector<Movie> movies = loadFile();
    std::vector<Movie> genreMovies = {};
    std::copy_if(movies.begin(), movies.end(), std::back_inserter(genreMovies), [&genreGiven](const Movie movie) {return movie.getGenre() == genreGiven; });
    if(genreMovies.empty())
        return movies;
    return genreMovies;
}

std::vector<Movie> FileRepository::getAllWatchListMovies() {
    std::vector<Movie> movies = loadUserFile();
    return movies;
}

Movie FileRepository::getMovieAtPosition(int positionOfMovie) {
    std::vector<Movie> movies = loadFile();
    if(positionOfMovie < 0 || positionOfMovie >= movies.size())
        throw RepositoryException(std::string("[Invalid Position]"));
    return movies[positionOfMovie];
}

int FileRepository::getNumberOfMovies() {
    std::vector<Movie> movies = loadFile();
    return movies.size();
}

int FileRepository::addMovieToWatchlist(const Movie &movieToAdd) {
    std::vector<Movie> movies = loadFile();
    auto temp = std::find(userWatchList.begin(), userWatchList.end(), movieToAdd);
    if(temp != userWatchList.end())
        throw RepositoryException(std::string("[Movie Already In Watch List]"));
    userWatchList.push_back(movieToAdd);
    return 1;
}

int FileRepository::addMovieToWatchListByTitle(const std::string &tempMovie) {
    std::vector<Movie> movies = loadFile();
    auto temp = std::find_if(movies.begin(), movies.end(), [&tempMovie](const Movie& movie) {return movie.getTitle() == tempMovie; });
    if(temp == movies.end())
        throw RepositoryException(std::string("[Movie Not Found]"));
    auto checkInList = std::find(userWatchList.begin(), userWatchList.end(), *temp);
    if(checkInList != userWatchList.end())
        throw RepositoryException(std::string("[Movie Already In Watch List"));
    userWatchList.push_back(*temp);
    writeUserFile(userWatchList);
    return 1;
}

int FileRepository::getNumberOfMoviesWatchList() {
    return userWatchList.size();
}

int FileRepository::deleteMovieFromWatchList(const std::string &title, bool liked) {
    this->userWatchList = loadUserFile();
    auto temp = std::find_if(userWatchList.begin(), userWatchList.end(), [&title](const Movie& movie) {return movie.getTitle() == title; });
    if(temp == userWatchList.end())
        throw RepositoryException(std::string("[Movie Not Found]"));
    if(liked)
        addLike(title);
    userWatchList.erase(temp);
    writeUserFile(userWatchList);
    return 1;
}

void FileRepository::addLike(const std::string &title) {
    std::vector<Movie> movies;
    movies = loadFile();
    auto temp = std::find_if(movies.begin(), movies.end(), [&title](const Movie& movie) {return movie.getTitle() == title; });
    temp->setLikes(temp->getLikes() + 1);
    writeFile(movies);
}

std::vector<Movie> FileRepository::loadUserFile() {
    std::vector<Movie> movies = {};
    Movie temp;
    if(userFileName.empty())
        changeUserFileName("user.txt");
    try {
        std::ifstream fin(userFileName);
        while(fin >> temp) {
            if(std::find(movies.begin(), movies.end(), temp) == movies.end())
                movies.push_back(temp);
        }
        fin.close();
        return movies;
    }
    catch (std::exception & e) {}
}

std::string FileRepository::getUserFileName() {
    return userFileName;
}

std::string FileRepository::getMainFileName() {
    return mainFileName;
}

void FileRepository::openFile() {
    ShellExecuteA(NULL, "open", userFileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

Movie FileRepository::getMovieByTitle(const std::string &title) {
    std::vector<Movie> movies = loadFile();
    auto temp = std::find_if(movies.begin(), movies.end(), [&title](const Movie& movie) {return movie.getTitle() == title; });
    if(temp == movies.end())
        throw RepositoryException(std::string("[Movie Not Found]"));
    return *temp;
}

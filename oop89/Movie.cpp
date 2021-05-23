//
// Created by araul on 28.03.2021.
//

#include "Movie.h"
#include <algorithm>
#include <iostream>

Movie::Movie(const std::string &movieTitle, const std::string &movieGenre, const std::string &movieTrailer, int movieRelease, int movieLikes) {
    title = movieTitle;
    genre = movieGenre;
    trailer = movieTrailer;
    year = movieRelease;
    likes = movieLikes;
}

const std::string& Movie::getTitle() const {
    return title;
}

void Movie::setTitle(const std::string &title) {
    Movie::title = title;
}

const std::string& Movie::getGenre() const {
    return genre;
}

void Movie::setGenre(const std::string &genre) {
    Movie::genre = genre;
}

const std::string& Movie::getTrailer() const {
    return trailer;
}

void Movie::setTrailer(const std::string &trailer) {
    Movie::trailer = trailer;
}

int Movie::getYear() const {
    return year;
}

void Movie::setYear(int year) {
    Movie::year = year;
}

int Movie::getLikes() const {
    return likes;
}

void Movie::setLikes(int likes) {
    Movie::likes = likes;
}

bool Movie::operator==(const Movie &movie) const {
    return title == movie.getTitle();
}

bool Movie::operator!=(const Movie &movie) const {
    return !(movie == *this);
}

void Movie::operator=(const Movie &movie) {
    title = movie.getTitle();
    genre = movie.getGenre();
    trailer = movie.getTrailer();
    year = movie.getYear();
    likes = movie.getLikes();
}

std::string Movie::toString() const {
    std::string movie = "Title: " + title + ", Genre: " + genre + ", Released: " + std::to_string(year) + ", Likes: " + std::to_string(likes) + ", Trailer: " + trailer + ";";
    return movie;
}

std::ostream &operator<<(std::ostream &out, const Movie &movie) {
    out << movie.toString();
    return out;
}

std::istream &operator>>(std::istream &in, Movie &movie) {
    std::string movieString;
    std::getline(in, movieString);
    if(movieString.empty())
        return in;
    movie.fromString(movieString);
    return in;
}

void Movie::fromString(std::string &toConvert) {
    std::vector<std::string> toDelete = {"Title: ", "Genre: ", "Released: ", "Likes: ", "Trailer: ", ";"};
    std::vector<std::string> finalString;
    size_t pos;

    for(const auto& i : toDelete)
    {
        pos = toConvert.find(i);
        if(pos != std::string::npos)
            toConvert.erase(pos, i.length());
    }

    std::string delimiter = ", ";
    std::string token;
    pos = 0;

    while ((pos = toConvert.find(delimiter)) != std::string::npos) {
        token = toConvert.substr(0, pos);
        finalString.push_back(token);
        toConvert.erase(0, pos + delimiter.length());
    }
    finalString.push_back(toConvert);

    this->setTitle(finalString[0]);
    this->setGenre(finalString[1]);
    this->setTrailer(finalString[4]);
    this->setYear(stoi(finalString[2]));
    this->setLikes(stoi(finalString[3]));
}

//
// Created by araul on 28.03.2021.
//
#include "AdminService.h"
#include "MovieValidator.h"

//AdminService constructor
AdminService::AdminService(Repository *repository) {
    this->repository = repository;
}

/*
	Add a movie in the list - title - title of the movie
							genre - genre of the movie
							yearOfRelease - the year when the movie was released
							numberOfLikes - trailer's number of likes
							trailer - link to the movie's trailer
*/
int AdminService::adminAddMovie(const std::string& title, const std::string& genre, int yearOfRelease, int numberOfLikes, const std::string& trailer)
{
    Movie movieUsed{ title, genre, trailer, yearOfRelease, numberOfLikes };
    MovieValidator::validate(movieUsed);
    return repository->addMovie(movieUsed);
}

/*
	Delete a movie from the list, by its title
*/
int AdminService::adminDeleteMovie(const std::string& title)
{
    Movie movieUsed{ title, "fillGenre", "No trailer", 1900, 0 };
    return repository->deleteMovie(movieUsed);
}

/*
	Update a movie in the list - title - title of the movie to be updated
							genre - genre of the movie to update with
							yearOfRelease - the year when the movie was released to update with
							numberOfLikes - trailer's number of likes to update with
							trailer - link to the movie's trailer to update with
*/
int AdminService::adminUpdateMovie(const std::string& title, const std::string& genre, int yearOfRelease, int numberOfLikes, const std::string& trailer)
{
    Movie movieUsed{ title, genre, trailer, yearOfRelease, numberOfLikes };;
    MovieValidator::validate(movieUsed);
    return repository->updateMovie(movieUsed);
}

//Return the list of movies
std::vector<Movie> AdminService::adminGetMovieList()
{
    return repository->getAllMovies();
}

void AdminService::populate() {
    adminAddMovie("The_Shawshank_Redemption", "Drama", 1994, 2367734, "https://www.imdb.com/video/vi3877612057?playlistId=tt0111161&ref_=tt_ov_vi");
    adminAddMovie("The_Godfather", "Drama", 1972, 1639457, "https://www.imdb.com/video/vi1348706585?playlistId=tt0068646&ref_=tt_ov_vi");
    adminAddMovie("The_Dark_Knight", "Action", 2008, 2330250, "https://www.imdb.com/video/vi324468761?playlistId=tt0468569&ref_=tt_ov_vi");
    adminAddMovie("12_Angry_Men", "Crime", 1957, 698568, "https://www.imdb.com/video/vi3452609817?playlistId=tt0050083&ref_=tt_ov_vi");
    adminAddMovie("Schindler's_List", "Drama", 1993, 1224635, "https://www.imdb.com/video/vi1158527769?playlistId=tt0108052&ref_=tt_ov_vi");
    adminAddMovie("LOTR:_The_Return_of_the_King", "Action", 2003, 1658040, "https://www.imdb.com/video/vi2073101337?playlistId=tt0167260&ref_=tt_ov_vi");
    adminAddMovie("Pulp_Fiction", "Crime", 1994, 2367734, "https://www.imdb.com/video/vi2620371481?playlistId=tt0110912&ref_=tt_ov_vi");
    adminAddMovie("The_Good,_the_Bad_and_the_Ugly", "Western", 1966, 694664, "https://www.imdb.com/video/vi3416964889?playlistId=tt0060196&ref_=tt_ov_vi");
    adminAddMovie("LOTR:_The_Fellowship_of_the_Ring", "Action", 2001, 1677771, "https://www.imdb.com/video/vi2073101337?playlistId=tt0120737&ref_=tt_ov_vi");
    adminAddMovie("Fight_Club", "Drama", 1999, 1874027, "https://www.imdb.com/video/vi781228825?playlistId=tt0137523&ref_=tt_ov_vi");
}

std::string AdminService::getFileName() {
    return repository->getMainFileName();
}

void AdminService::changeFileName(const std::string &name) {
    repository->changeMainFileName(name);
}

void AdminService::changeRepo(Repository* repo) {
    this->repository = repo;
}

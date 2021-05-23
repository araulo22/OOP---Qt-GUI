//
// Created by araul on 28.03.2021.
//
#include "UI.h"
#include <iostream>
#include <windows.h>
#include <shellapi.h>
UI::UI(AdminService& adminService, UserService& userService, Repository& mrepo, FileRepository& frepo, CSVRepository& crepo, HTMLRepository& hrepo):
adminService { adminService }, userService{ userService }, memoryRepo{ mrepo }, txtRepo{ frepo }, csvRepo{ crepo }, htmlRepo{ hrepo} {}

void UI::runApp()
{
    std::string command;
    while (true) {
        std::cout << "Choose: launch / changeRepo / exit\n";
        std::cout << "Admin Repository: " << adminService.getFileName() << std::endl;
        std::cout << "User Repository: " << userService.getFileName() << std::endl;
        std::cout << "Command: ";
        std::cin >> command;
        if (command == "launch") {
            std::cout << "Choose: ADMIN / USER\n";
            std::cin >> command;
            if (command == "ADMIN")
                runAdmin();
            else
                if (command == "USER")
                    runUser();
                else
                    std::cout << "Invalid input!\n";
            break;
        }
        else if (command == "changeRepo")
            uiChangeRepo();
        else if (command == "exit")
            break;
        else
            std::cout << "Invalid input!\n";
    }
}

void UI::runAdmin()
{
    std::cout << "Administrator mode enabled!\n";
    std::string consoleInput;
    int changeMode = 0;
    while (true && !changeMode) {
        std::cout << "Admin Repository: " << adminService.getFileName() << std::endl;
        std::cout << "User Repository: " << userService.getFileName() << std::endl;
        std::cout << "Choose: add / update / delete / list / mode / changeFile / exit\n";
        std::cout << "Input: ";
        std::cin >> consoleInput;
        if (consoleInput == "add")
            uiAdminAdd();
        else if (consoleInput == "update")
            uiAdminUpdate();
        else if (consoleInput == "delete")
            uiAdminDelete();
        else if (consoleInput == "list")
            uiAdminList();
        else if (consoleInput == "changeFile")
            uiAdminChangeFile();
        else if (consoleInput == "mode") {
            std::string modeToChange;
            std::cout << "Choose: ADMIN / USER\n";
            std::cin >> modeToChange;
            if (modeToChange == "USER") {
                changeMode = 1;
                runUser();
            }
        }
        else if (consoleInput == "exit")
            break;
        else
            std::cout << "Invalid input! \n";
    }

}

void UI::runUser()
{
    std::cout << "User mode enabled!\n";
    Movie currentMovie;
    std::string consoleInput;
    int changeMode = 0;
    while (true && !changeMode && !inList) {
        std::cout << "User Repository: " << userService.getFileName() << std::endl;
        std::cout << "Choose: list / next / watchList / save / remove / changeFile / openFile / mode / exit\n";
        std::cout << "Movie format: <title> <genre> <year> <likes> <trailer>\n";
        std::cout << "Input: ";
        std::cin >> consoleInput;
        if (consoleInput == "list") {
            inList = true;
            uiUserList();
        }
        else if (consoleInput == "mode") {
            std::string modeToChange;
            std::cout << "Choose: ADMIN / USER\n";
            std::cin >> modeToChange;
            if (modeToChange == "ADMIN") {
                changeMode = 1;
                runAdmin();
            }
        }
        else if (consoleInput == "next") {
            currentMovie = userService.getCurrentMovie();
            std::cout << currentMovie;
            uiUserNext();
        }
        else if (consoleInput == "watchList")
            uiUserWatchList();
        else if (consoleInput == "save")
            uiUserSave();
        else if (consoleInput == "remove")
            uiUserRemove();
        else if (consoleInput == "exit")
            break;
        else if (consoleInput == "changeFile")
            uiUserChangeFile();
        else if (consoleInput == "openFile")
            uiUserOpenFile();
        else
            std::cout << "Invalid input! \n";
    }
}

void UI::uiAdminAdd()
{
    std::string title, genre, trailer, consoleInput;
    int yearOfRelease, numberOfLikes;

    std::cout << "> Title: ";
    std::cin >> consoleInput;
    title = consoleInput;

    std::cout << "> Genre: ";
    std::cin >> consoleInput;
    genre = consoleInput;

    std::cout << "> Year of release: ";
    std::cin >> consoleInput;
    yearOfRelease = stoi(consoleInput);

    std::cout << "> Number or likes: ";
    std::cin >> consoleInput;
    numberOfLikes = stoi(consoleInput);

    std::cout << "> Trailer: ";
    std::cin >> consoleInput;
    trailer = consoleInput;

    try {
        adminService.adminAddMovie(title, genre, yearOfRelease, numberOfLikes, trailer);
    } catch(std::exception& exception) {
        std::cout << exception.what() << '\n';
    }
}

void UI::uiAdminDelete()
{
    std::cout << "> Title: \n";
    std::string title, consoleInput;
    std::cin >> consoleInput;
    title = consoleInput;

    try {
        adminService.adminDeleteMovie(title);
    } catch(std::exception& exception) {
        std::cout << exception.what() << '\n';
    }
}

void UI::uiAdminUpdate()
{
    std::string title, genre, trailer, consoleInput;
    int yearOfRelease, numberOfLikes;

    std::cout << "> Title: ";
    std::cin >> consoleInput;
    title = consoleInput;

    std::cout << "> Genre: ";
    std::cin >> consoleInput;
    genre = consoleInput;

    std::cout << "> Year of release: ";
    std::cin >> consoleInput;
    yearOfRelease = stoi(consoleInput);

    std::cout << "> Number or likes: ";
    std::cin >> consoleInput;
    numberOfLikes = stoi(consoleInput);

    std::cout << "> Trailer: ";
    std::cin >> consoleInput;
    trailer = consoleInput;

    try {
        adminService.adminUpdateMovie(title, genre, yearOfRelease, numberOfLikes, trailer);
    } catch(std::exception& exception) {
        std::cout << exception.what() << '\n';
    }
}

void UI::uiAdminList()
{
    std::vector<Movie>listOfMovies = adminService.adminGetMovieList();
    for (auto & listOfMovie : listOfMovies)
        std::cout << listOfMovie << '\n';
}

void UI::uiUserAdd() {
    int isFunctionSuccessful = userService.addMovieToWatchList();
    if (isFunctionSuccessful == -1)
        std::cout << "ERROR: Failed to add movie!\n";
}

void UI::uiUserWatchList()
{
    std::vector<Movie>listOfMovies = userService.userGetWatchList();
    for (auto & listOfMovie : listOfMovies)
        std::cout << listOfMovie << '\n';
}

void UI::uiUserNext() {
    userService.goToNextMovieByGenre();
}

void UI::uiUserSave()
{
    std::cout << "Movie title: \n";
    std::string title;
    std::cin >> title;
    int isFunctionSuccessful = userService.addMovieToWatchListByTitle(title);
    if (isFunctionSuccessful == -1)
        std::cout << "ERROR: Invalid movie!\n";
}

void UI::uiUserList()
{

    std::string consoleInput, genre;
    Movie currentMovie;
    std::cout << "*If no movies of the given genre are found, all movies are shown\n";
    std::cout << "Specify a genre: \n";
    std::cin >> genre;
    int isFunctionSuccessful = userService.listMoviesByGenre(genre);
    if (isFunctionSuccessful == -1)
        std::cout << "ERROR: Failed to select movies!\n";
    while (isFunctionSuccessful != -1 && inList) {
        try {
            currentMovie = userService.getCurrentMovie();
        }
        catch (std::exception &Exception) {
            std::cout << Exception.what() << '\n';
        }
        std::cout << currentMovie << '\n';
        ShellExecuteA(NULL, "open", userService.getCurrentMovie().getTrailer().c_str(), NULL, NULL, SW_SHOWNORMAL);
        std::cout << "Commands: add / next / exit \n";
        std::cout << "Input: ";
        std::cin >> consoleInput;
        if (consoleInput == "add") {
            uiUserAdd();
            uiUserNext();
        }
        else if (consoleInput == "next")
            uiUserNext();
        else if (consoleInput == "exit")
            inList = false;
        else
            std::cout << "Invalid input!\n";
    }

}

void UI::uiUserRemove() {
    std::cout << "Movie title: \n";
    std::string title, enjoy;
    std::cin >> title;
    std::cout << "Did you enjoy the movie? Type <yes> to add a like!\n";
    std::cin >> enjoy;
    bool liked = false;
    if(enjoy == "yes")
        liked = true;
    int isFunctionSuccessful = userService.removeMovieFromWatchList(title, liked);
    if (isFunctionSuccessful == -1)
        std::cout << "ERROR: Invalid movie!\n";
}

void UI::uiAdminChangeFile() {
    std::cout << "> File Name: \n";
    std::string name, consoleInput;
    std::cin >> consoleInput;
    name = consoleInput;

    try {
        adminService.changeFileName(name);
    } catch(std::exception& exception) {
        std::cout << exception.what() << '\n';
    }
}

void UI::uiUserChangeFile() {
    std::cout << "> File Name: \n";
    std::string name, consoleInput;
    std::cin >> consoleInput;
    name = consoleInput;

    try {
        userService.changeFileName(name);
    } catch(std::exception& exception) {
        std::cout << exception.what() << '\n';
    }
}

void UI::uiChangeRepo() {
    std::cout << "> Repo Type (txt, csv, html, memory): \n";
    std::string name, consoleInput;
    std::cin >> consoleInput;
    name = consoleInput;
    if(name != "txt" && name != "csv" && name != "html" && name != "memory")
        std::cout << "ERROR: Invalid repository type!\n";
    else {
        if(name == "memory") {
            userService.changeRepo(&memoryRepo);
            adminService.changeRepo(&memoryRepo);
        }
        else if(name == "txt") {
            userService.changeRepo(&txtRepo);
            adminService.changeRepo(&txtRepo);
        }
        else if(name == "html") {
            userService.changeRepo(&htmlRepo);
            adminService.changeRepo(&htmlRepo);
        }
        else if(name == "csv") {
            userService.changeRepo(&csvRepo);
            adminService.changeRepo(&csvRepo);
        }
    }
    std::cout << "Successfully changed repository type!\n";
}

void UI::uiUserOpenFile() {
    userService.openFile();
}


#include "gui.h"
#include <QFormLayout>
#include <qgridlayout.h>
#include "Movie.h"
#include <vector>
#include <qmessagebox.h>
#include <exception>
#include <QLabel>

GUI::GUI(AdminService &adminService, UserService &userService): adminService{adminService}, userService{userService}{initAdminGUI(); initUserGUI(); populateList(); connectSignalsAndSlots();}

void GUI::initAdminGUI() {
    mainLayout->addWidget(this->adminWidget);
    mainLayout->addWidget(this->userWidget);

    this->mainAdminLayout->addWidget(new QLabel("Admin"));
    this->mainAdminLayout->addWidget(new QLabel("Movie List:"));
    this->mainUserLayout->addWidget(new QLabel("User"));
    this->adminWidget->setVisible(true);
    this->userWidget->setVisible(false);

    this->movieListWidget = new QListWidget();

    this->titleLineEdit = new QLineEdit();
    this->genreLineEdit = new QLineEdit();
    this->yearLineEdit = new QLineEdit();
    this->likesLineEdit = new QLineEdit();
    this->trailerLineEdit = new QLineEdit();

    this->addButton = new QPushButton("Add / Update");
    this->deleteButton = new QPushButton("Delete");
    this->changeModeButton = new QPushButton("Change Mode");
    this->exitButton = new QPushButton("Exit");


    mainAdminLayout->addWidget(this->movieListWidget);

    QFormLayout* movieDetailsLayout = new QFormLayout();
    movieDetailsLayout->addRow("Title", this->titleLineEdit);
    movieDetailsLayout->addRow("Genre", this->genreLineEdit);
    movieDetailsLayout->addRow("Year of release", this->yearLineEdit);
    movieDetailsLayout->addRow("Number of likes", this->likesLineEdit);
    movieDetailsLayout->addRow("Trailer", this->trailerLineEdit);

    mainAdminLayout->addLayout(movieDetailsLayout);

    QGridLayout* buttonsLayout = new QGridLayout();
    buttonsLayout->addWidget(this->addButton, 0, 0);
    buttonsLayout->addWidget(this->deleteButton, 0, 1);
    buttonsLayout->addWidget(this->changeModeButton, 1, 0);
    buttonsLayout->addWidget(this->exitButton, 1, 1);

    mainAdminLayout->addLayout(buttonsLayout);
}

void GUI::initUserGUI() {
    /*    QListWidget* watchListWidget;
    QLineEdit* userGenreLineEdit, *userTitleLineEdit;
    QPushButton* userListButton, *userNextButton, *userAddButton, *userRemoveButton, *userTrailerButton, *userOpenWatchListButton;*/

    this->watchListWidget = new QListWidget();
    this->filteredListWidget = new QListWidget();
    mainUserLayout->addWidget(new QLabel("Movie List:"));
    mainUserLayout->addWidget(this->filteredListWidget);

    this->userTitleLineEdit = new QLineEdit();
    this->userGenreLineEdit = new QLineEdit();

    this->userListButton = new QPushButton("Filter by Genre");
    this->userAddButton = new QPushButton("Save to WatchList by Title");
    this->userRemoveButton = new QPushButton("Remove by Title");
    this->userTrailerButton = new QPushButton("View Trailer");
    this->userOpenWatchListButton = new QPushButton("Open Watch List File");
    this->userChangeModeButton = new QPushButton("Change Mode");
    this->userExitButton = new QPushButton("Exit");
    this->likedMovieCheckBox = new QCheckBox("I liked the movie!", userWidget);

    QFormLayout* filterLayout = new QFormLayout();
    filterLayout->addRow("Genre", this->userGenreLineEdit);

    mainUserLayout->addLayout(filterLayout);
    mainUserLayout->addWidget(userListButton);

    QFormLayout* editWatchListLayout = new QFormLayout();
    editWatchListLayout->addRow("Title", this->userTitleLineEdit);

    mainUserLayout->addLayout(editWatchListLayout);

    QGridLayout* userButtonsLayout = new QGridLayout();
    userButtonsLayout->addWidget(this->userAddButton, 0, 0);
    userButtonsLayout->addWidget(this->userRemoveButton, 1, 0);
    userButtonsLayout->addWidget(this->userTrailerButton, 0, 1);
    userButtonsLayout->addWidget(likedMovieCheckBox, 1, 1);

    mainUserLayout->addLayout(userButtonsLayout);
    mainUserLayout->addWidget(new QLabel("Watch List:"));
    mainUserLayout->addWidget(watchListWidget);
    mainUserLayout->addWidget(userOpenWatchListButton);


    QGridLayout* userButtonsLayout2 = new QGridLayout();
    userButtonsLayout2->addWidget(this->userChangeModeButton, 0, 0);
    userButtonsLayout2->addWidget(this->userExitButton, 0, 1);

    mainUserLayout->addLayout(userButtonsLayout2);
}

void GUI::populateList() {

    this->movieListWidget->clear();
    std::vector<Movie> allMovies = this->adminService.adminGetMovieList();
    for(Movie& movieUsed: allMovies)
        this->movieListWidget->addItem(QString::fromStdString(movieUsed.toString()));
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->movieListWidget, &QListWidget::itemSelectionChanged, [this](){
        int selectedIndex = this->getSelectedIndex();
        if(selectedIndex < 0)
            return;
        Movie movieUsed = this->adminService.adminGetMovieList()[selectedIndex];
        this->titleLineEdit->setText(QString::fromStdString(movieUsed.getTitle()));
        this->genreLineEdit->setText(QString::fromStdString(movieUsed.getGenre()));
        this->yearLineEdit->setText(QString::fromStdString(std::to_string(movieUsed.getYear())));
        this->likesLineEdit->setText(QString::fromStdString(std::to_string(movieUsed.getLikes())));
        this->trailerLineEdit->setText(QString::fromStdString(movieUsed.getTrailer()));
    });
    QObject::connect(this->filteredListWidget, &QListWidget::itemSelectionChanged, [this](){
        int selectedIndex = this->getUserFilteredSelectedIndex();
        if(selectedIndex < 0)
            return;
        Movie movieUsed = this->userService.userGetCurrentMoviesByGenre()[selectedIndex];
        this->userTitleLineEdit->setText(QString::fromStdString(movieUsed.getTitle()));
    });
    QObject::connect(this->watchListWidget, &QListWidget::itemSelectionChanged, [this](){
        int selectedIndex = this->getUserWatchListSelectedIndex();
        if(selectedIndex < 0)
            return;
        Movie movieUsed = this->userService.userGetWatchList()[selectedIndex];
        this->userTitleLineEdit->setText(QString::fromStdString(movieUsed.getTitle()));
    });

    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addMovie);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteMovie);
    QObject::connect(this->changeModeButton, &QPushButton::clicked, this, &GUI::changeMode);
    QObject::connect(this->exitButton, &QPushButton::clicked, this, &GUI::exitApp);
    QObject::connect(this->userChangeModeButton, &QPushButton::clicked, this, &GUI::changeMode);
    QObject::connect(this->userExitButton, &QPushButton::clicked, this, &GUI::exitApp);
    QObject::connect(this->userListButton, &QPushButton::clicked, this, &GUI::userList);
    QObject::connect(this->userAddButton, &QPushButton::clicked, this, &GUI::userSave);
    QObject::connect(this->userOpenWatchListButton, &QPushButton::clicked, this, &GUI::userOpenFile);
    QObject::connect(this->userRemoveButton, &QPushButton::clicked, this, &GUI::userRemove);
    QObject::connect(this->userTrailerButton, &QPushButton::clicked, this, &GUI::userTrailer);
}

int GUI::getSelectedIndex() const {
    QModelIndexList selectedIndexes = this->movieListWidget->selectionModel()->selectedIndexes();
    if(selectedIndexes.size() == 0){
        this->titleLineEdit->clear();
        this->genreLineEdit->clear();
        this->yearLineEdit->clear();
        this->likesLineEdit->clear();
        this->trailerLineEdit->clear();
        return -1;
    }

    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

int GUI::getUserFilteredSelectedIndex() const {
    QModelIndexList selectedIndexes = this->filteredListWidget->selectionModel()->selectedIndexes();
    if(selectedIndexes.size() == 0){
        this->userTitleLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

int GUI::getUserWatchListSelectedIndex() const {
    QModelIndexList selectedIndexes = this->watchListWidget->selectionModel()->selectedIndexes();
    if(selectedIndexes.size() == 0){
        this->userTitleLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void GUI::addMovie() {
    int selectedIndex = this->getSelectedIndex();
    if(selectedIndex < 0){
        QMessageBox::critical(this, "Error", "No movie selected!");
        return;
    }
    std::string title = this->titleLineEdit->text().toStdString();
    std::string genre = this->genreLineEdit->text().toStdString();
    std::string stringYearOfRelease = this->yearLineEdit->text().toStdString();
    std::string stringNumberOfLikes = this->likesLineEdit->text().toStdString();
    std::string trailer = this->trailerLineEdit->text().toStdString();

    int yearOfRelease = stoi(stringYearOfRelease);
    int numberOfLikes = stoi(stringNumberOfLikes);
    Movie movieUsed{title, genre, trailer, yearOfRelease, numberOfLikes};
    std::vector<Movie>movieList = this->adminService.adminGetMovieList();
    if(std::find(movieList.begin(), movieList.end(), movieUsed) != movieList.end())
        try{
            this->adminService.adminUpdateMovie(title, genre, yearOfRelease, numberOfLikes, trailer);
        }
        catch(std::exception& e){
            QMessageBox::critical(this, "Error", e.what());
            return;
        }
    else
        try {
            this->adminService.adminAddMovie(title, genre, yearOfRelease, numberOfLikes, trailer);
        }
        catch(std::exception& e){
            QMessageBox::critical(this, "Error", e.what());
            return;
        }
    this->populateList();
}

void GUI::deleteMovie() {
    int selectedIndex = this->getSelectedIndex();
    if(selectedIndex < 0){
        QMessageBox::critical(this, "Error", "No movie selected!");
        return;
    }
    std::string title = this->titleLineEdit->text().toStdString();
    try{
        this->adminService.adminDeleteMovie(title);
    }
    catch(std::exception& e){
        QMessageBox::critical(this, "Error", e.what());
        return;
    }

    this->populateList();

}

void GUI::changeMode() {
    if(adminMode) {
        adminMode = false;
        this->populateWatchList();
        this->adminWidget->setVisible(false);
        this->userWidget->setVisible(true);
    } else {
        adminMode = true;
        this->populateList();
        this->adminWidget->setVisible(true);
        this->userWidget->setVisible(false);
    }
}

void GUI::exitApp() {
    this->close();
}

void GUI::populateWatchList() {
    this->watchListWidget->clear();
    std::vector<Movie> allMovies = this->userService.userGetWatchList();
    for(Movie& movieUsed: allMovies)
        this->watchListWidget->addItem(QString::fromStdString(movieUsed.toString()));
}

void GUI::userList() {
    std::string title = this->userGenreLineEdit->text().toStdString();
    try {
        this->filteredListWidget->clear();
        this->userService.listMoviesByGenre(title);
        std::vector<Movie> allMovies = this->userService.userGetCurrentMoviesByGenre();
        for(Movie& movieUsed: allMovies)
            this->filteredListWidget->addItem(QString::fromStdString(movieUsed.toString()));
    }
    catch(std::exception& e){
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
}

void GUI::userSave() {
    std::string title = this->userTitleLineEdit->text().toStdString();
    try {
        this->userService.addMovieToWatchListByTitle(title);
    }
    catch(std::exception& e){
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    this->populateWatchList();
}

void GUI::userOpenFile() {
    this->userService.openFile();
}

void GUI::userRemove() {
    std::string title = this->userTitleLineEdit->text().toStdString();
    bool liked = this->likedMovieCheckBox->isChecked();
    try {
        this->userService.removeMovieFromWatchList(title, liked);
    }
    catch(std::exception& e){
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    this->populateWatchList();
}

void GUI::userTrailer() {
    std::string title = this->userTitleLineEdit->text().toStdString();
    try {
        Movie temp = this->userService.getMovieByTitle(title);
        ShellExecuteA(NULL, "open", temp.getTrailer().c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
    catch(std::exception& e){
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
}

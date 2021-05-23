#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QListWidget.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include "AdminService.h"
#include "UserService.h"
#include <QCheckBox>

class GUI : public QWidget
{
private:
    AdminService& adminService;
    UserService& userService;

    QVBoxLayout* mainLayout = new QVBoxLayout{this};

    QWidget* adminWidget = new QWidget();
    QWidget* userWidget = new QWidget();
    QVBoxLayout* mainAdminLayout = new QVBoxLayout{adminWidget};
    QVBoxLayout* mainUserLayout = new QVBoxLayout{userWidget};

    QListWidget* movieListWidget;
    QLineEdit* titleLineEdit, *genreLineEdit, *yearLineEdit, *likesLineEdit, *trailerLineEdit;
    QPushButton* addButton, * deleteButton, *changeModeButton, *exitButton;

    QListWidget* watchListWidget, *filteredListWidget;
    QLineEdit* userGenreLineEdit, *userTitleLineEdit;
    QPushButton* userListButton, *userAddButton, *userRemoveButton, *userTrailerButton, *userOpenWatchListButton, *userChangeModeButton, *userExitButton;
    QCheckBox* likedMovieCheckBox;

    bool adminMode = true;
    void initAdminGUI();
    void initUserGUI();
    void populateList();
    void connectSignalsAndSlots();
    int getSelectedIndex() const;
    void addMovie();
    void deleteMovie();
    void changeMode();
    void exitApp();

    void populateWatchList();
    void userList();
    void userWatchList();
    void userSave();
    void userRemove();
    void userTrailer();
    void userOpenFile();
    int getUserFilteredSelectedIndex() const;
    int getUserWatchListSelectedIndex() const;

public:
    GUI(AdminService& adminService, UserService& userService);

signals:

};

#endif // GUI_H

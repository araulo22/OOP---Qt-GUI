#include "mainwindow.h"
#include "gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileRepository* repo = new FileRepository("data.txt");
    AdminService adminService{repo};
    UserService userService{repo};
    GUI gui{adminService, userService};
    gui.show();
    return a.exec();
}

//
// Created by sauvau_m on 4/18/17.
//

#include "QtWidgets/QApplication"
#include "QtWidgets/QPushButton"
#include "QtWidgets/QLineEdit"
#include <QtWidgets/QMainWindow>

int main(int ac, char **av)
{
    QApplication app(ac, av);
    QMainWindow mainWindow;

    mainWindow.setFixedSize(800, 800);
    QPushButton hello("blabla!", &mainWindow);
    QLineEdit txt(&mainWindow);

    txt.move(0, 100);
    txt.setFixedSize(400, 20);
    txt.setText("Hello, world!");
    mainWindow.show();
    return app.exec();
}
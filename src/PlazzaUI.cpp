//
// Created by sauvau_m on 4/20/17.
//

#include <iostream>
#include "PlazzaUI.hpp"

plazza::PlazzaUI::~PlazzaUI() {

}

plazza::PlazzaUI::PlazzaUI(int ac, char **av) : app(ac, av), buttonAddFile("Add File", &mainWindow),
                                                btnExecute("Execute", &mainWindow),
                                                cmdLine(&mainWindow), cmdLineLabel("Enter File Path :", &mainWindow),
                                                scrollAreaLabel("Added Files :", &mainWindow),
                                                scrollAreaWidget(new QWidget()), scrollArea(&mainWindow) {

    scrollAreaWidget->setLayout(&scrollArealayout);
    mainWindow.setFixedSize(800, 800);
    cmdLineLabel.move(0, 5);
    scrollAreaLabel.move(0, cmdLine.pos().y() + cmdLine.height() + 10);
    cmdLine.move(cmdLineLabel.width() + 5, cmdLineLabel.pos().y());
    cmdLine.setFixedSize(550, 30);
    buttonAddFile.move(cmdLineLabel.width() + 5 + cmdLine.width() + 10, cmdLine.pos().y());
    QObject::connect(&buttonAddFile, &QPushButton::clicked, [this] { addFile(); });
    scrollArea.setFixedSize(660, 350);
    scrollArea.move(cmdLineLabel.width() + 5, cmdLine.pos().y() + cmdLine.height() + 10);
    scrollArea.setWidgetResizable(true);
    btnExecute.move(cmdLineLabel.width() + 5 + cmdLine.width() + 10, scrollArea.pos().y() + scrollArea.height() + 10);
    QObject::connect(&btnExecute, &QPushButton::clicked, [this] { execute(); });
    mainWindow.show();
}

const QApplication &plazza::PlazzaUI::getApp() const {
    return app;
}

void plazza::PlazzaUI::addFile() {

    if (cmdLine.text() != "") {
        QWidget *widget = new QWidget();
        QHBoxLayout *hlayout = new QHBoxLayout(widget);
        QLabel *label = new QLabel(cmdLine.text());
        QCheckBox *phone = new QCheckBox("Phone");
        QCheckBox *email = new QCheckBox("Email");
        QCheckBox *ip = new QCheckBox("Ip");
        cmdLine.clear();

        label->setFixedSize(475, 20);
        phone->setFixedSize(55, 20);
        email->setFixedSize(50, 20);
        ip->setFixedSize(30, 20);
        hlayout->addWidget(label);
        hlayout->addWidget(phone);
        hlayout->addWidget(email);
        hlayout->addWidget(ip);

        files.push_back(UIAddedFile(label, phone, email, ip));
        scrollArealayout.addWidget(widget);
        scrollArea.setWidget(scrollAreaWidget);
    }
}

void plazza::PlazzaUI::execute() {
    for (size_t i = 0; i < files.size(); ++i) {

        std::cout << files[i].getLabel().text().toStdString() << " " << files[i].getPhone().isChecked() << std::endl;
    }
}
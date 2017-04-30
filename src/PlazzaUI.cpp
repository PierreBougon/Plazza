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
                                                scrollAreaWidget(new QWidget()), scrollArea(&mainWindow),
                                                scrollAreaWidgetThread(new QWidget()), scrollAreaThread(&mainWindow),
                                                processHandler(std::stoul(av[1]), av[0]),
                                                nbThreadsMax(std::stoul(av[1])),
                                                timer(new QTimer()) {

    scrollAreaWidget->setLayout(&scrollArealayout);
    scrollAreaWidgetThread->setLayout(&scrollArealayoutThread);

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

    scrollAreaThread.setFixedSize(750, 340);
    scrollAreaThread.move(20, scrollArea.pos().y() + scrollArea.height() + btnExecute.height() + 20);
    scrollAreaThread.setWidgetResizable(true);
    timer->setInterval(100);
    QObject::connect(timer, &QTimer::timeout, [this] { getProcessInfos(); });
    timer->start(100);
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
    std::vector<command> cmds;

    for (size_t i = 0; i < files.size(); ++i) {
        if (files[i].getEmail().isChecked())
            cmds.push_back(command(files[i].getLabel().text().toStdString(), EMAIL_ADDRESS));
        if (files[i].getPhone().isChecked())
            cmds.push_back(command(files[i].getLabel().text().toStdString(), PHONE_NUMBER));
        if (files[i].getIp().isChecked())
            cmds.push_back(command(files[i].getLabel().text().toStdString(), IP_ADDRESS));
    }

    processHandler.feed(cmds);
    QLayoutItem *item = NULL;
    while ((item = scrollArealayout.takeAt(0)) != 0)
        delete item->widget();
    files.clear();
}

void plazza::PlazzaUI::getProcessInfos() {

    QLayoutItem *item = NULL;
    while ((item = scrollArealayoutThread.takeAt(0)) != 0)
        delete item->widget();

    QWidget *widget = new QWidget();
    QHBoxLayout *hlayout = new QHBoxLayout(widget);

    for (size_t i = 0; i < processHandler.getProcessOccupancy().size(); ++i) {

        QLabel *process = new QLabel("Process " + QString::fromStdString(std::to_string(i)) + " : ");
        hlayout->addWidget(process);
        QLabel *threads = new QLabel(
                QString::fromStdString(std::to_string(processHandler.getProcessOccupancy()[i])) + " / " +
                QString::fromStdString(std::to_string(nbThreadsMax)) + " working threads");
        hlayout->addWidget(threads);
    }
    scrollArealayoutThread.addWidget(widget);
    scrollAreaThread.setWidget(scrollAreaWidgetThread);
}

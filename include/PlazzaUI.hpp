//
// Created by sauvau_m on 4/20/17.
//

#ifndef CPP_PLAZZA_PLAZZAUI_HPP
#define CPP_PLAZZA_PLAZZAUI_HPP


#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtCore/QTimer>
#include <memory>
#include "UIAddedFile.hpp"
#include "ProcessHandler.hpp"

namespace plazza {

    class PlazzaUI {

        size_t nbThreadsMax;
        QApplication app;
        QMainWindow mainWindow;
        QPushButton buttonAddFile;
        QPushButton btnExecute;
        QLineEdit cmdLine;
        QLabel cmdLineLabel;
        QLabel scrollAreaLabel;
        QWidget *scrollAreaWidget;
        QScrollArea scrollArea;
        QVBoxLayout scrollArealayout;
        QWidget *scrollAreaWidgetThread;
        QScrollArea scrollAreaThread;
        QVBoxLayout scrollArealayoutThread;
        std::vector<UIAddedFile> files;
        QTimer *timer;


        PlazzaUI() = delete;
        void addFile();
        void execute();
        void getProcessInfos();

    public:
        ProcessHandler processHandler;

        virtual ~PlazzaUI();
        PlazzaUI(int ac, char **av);
        const QApplication &getApp() const;
    };
}
#endif //CPP_PLAZZA_PLAZZAUI_HPP

//
// Created by sauvau_m on 4/20/17.
//

#ifndef CPP_PLAZZA_UIADDEDFILE_HPP
#define CPP_PLAZZA_UIADDEDFILE_HPP

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QScrollArea>

namespace plazza {
    class UIAddedFile {

        QLabel *label;
        QCheckBox *phone;
        QCheckBox *email;
        QCheckBox *ip;

    public:
        virtual ~UIAddedFile();

        UIAddedFile(QLabel *label, QCheckBox *phone, QCheckBox *email, QCheckBox *ip);

        const QLabel &getLabel() const;

        const QCheckBox &getPhone() const;

        const QCheckBox &getEmail() const;

        const QCheckBox &getIp() const;

    };
}

#endif //CPP_PLAZZA_UIADDEDFILE_HPP

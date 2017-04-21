//
// Created by sauvau_m on 4/20/17.
//

#include "UIAddedFile.hpp"
#include <QtWidgets/QScrollArea>

plazza::UIAddedFile::~UIAddedFile() {

}


plazza::UIAddedFile::UIAddedFile(QLabel *label, QCheckBox *phone, QCheckBox *email, QCheckBox *ip) : label(label),
                                                                                                     phone(phone),
                                                                                                     email(email),
                                                                                                     ip(ip) {}

const QLabel &plazza::UIAddedFile::getLabel() const {
    return *label;
}

const QCheckBox &plazza::UIAddedFile::getPhone() const {
    return *phone;
}

const QCheckBox &plazza::UIAddedFile::getEmail() const {
    return *email;
}

const QCheckBox &plazza::UIAddedFile::getIp() const {
    return *ip;
}

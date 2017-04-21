//
// Created by sauvau_m on 4/18/17.
//

#include <PlazzaUI.hpp>

int main(int ac, char **av)
{
    plazza::PlazzaUI ui(ac, av);
    return ui.getApp().exec();
}
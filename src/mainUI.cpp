//
// Created by sauvau_m on 4/18/17.
//

#include <PlazzaUI.hpp>
#include <iostream>

//#ifdef UI
int main(int ac, char **av)
{
    if (ac != 2 || std::stoi(av[1]) <= 0) {
        std::cerr << "usage : ./plazza nb_thread_per_process" << std::endl;
        return (1);
    }

    plazza::PlazzaUI ui(ac, av);
    return ui.getApp().exec();
}
//#endif
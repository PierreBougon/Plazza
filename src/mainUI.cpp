//
// Created by sauvau_m on 4/18/17.
//

#include <PlazzaUI.hpp>

//#ifdef UI
int main(int ac, char **av)
{
    plazza::PlazzaUI ui(ac, av);
    return ui.getApp().exec();
}
//#endif
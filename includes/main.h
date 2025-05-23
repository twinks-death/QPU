#ifndef MAIN_H
#define MAIN_H

// Utilities for main.c

// Clears the terminal, when recieves enter keystroke
// If platform is Windows - uses system cls,
// Otherwise              - uses system clear.
void wait_for_enter(void)
{
    while (getchar() != '\n');
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

#endif //MAIN_H

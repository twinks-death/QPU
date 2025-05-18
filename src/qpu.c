#include "qpu-lib.h"
#include "SDL3/SDL.h"
#include <stdio.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("SDL3 Test Window",640, 480, SDL_WINDOW_OPENGL);
    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Wait for 2 seconds
    SDL_Delay(2000);

    SDL_DestroyWindow(win);
    SDL_Quit();

    printf("SDL window opened and closed successfully.\n");
    return 0;
}


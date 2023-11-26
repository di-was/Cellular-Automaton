#include <SDL2/SDL.h>
#include <stdio.h>
#include "constants.h"

//------- GLOBAL VARIABLES----------
SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;
short int in_game = FALSE;

// Initialize SDL, boot window and renderer 
short int initialize() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL. \n");
        return FALSE;
    }

    window = SDL_CreateWindow(
        "Game of life",
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        fprintf(stderr, "Error creating Window");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        fprintf(stderr, "Error creating renderer");
        return FALSE;
    }

    return TRUE;
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            in_game = FALSE;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                in_game = FALSE;
            }
            break;
    }
}

void draw_grid() {
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);

    int total_lines_vertically = window_width / BLOCK_WIDTH;
    int total_lines_horizontally = window_height / BLOCK_HEIGHT;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Render vertical lines

    for (int i =1; i <= total_lines_vertically; i++) {
        SDL_RenderDrawLine(renderer,  BLOCK_WIDTH * i, 0, BLOCK_WIDTH*i, window_height);
    }

    // Render horizontal lines

    for (int i=1; i <= total_lines_horizontally; i++) {
        SDL_RenderDrawLine(renderer, 0, BLOCK_HEIGHT*i, window_width, BLOCK_HEIGHT*i);
    }
    
}

void render() {
    SDL_SetRenderDrawColor(renderer, 29, 26, 30, 0.8);
    SDL_RenderClear(renderer); // fills the screen with the last set color
     
    //------------ OBJECTS RENDERING BLOCK------------

    draw_grid();

    //---------END OF OBJECTS RENDERING BLOCK---------

    SDL_RenderPresent(renderer); // switches the buffer frame
}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void) {
    in_game = initialize();

    while (in_game) {
        process_input();
        render();
    }
    destroy_window();
    return 0;    
}
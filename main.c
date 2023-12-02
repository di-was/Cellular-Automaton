#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "engine.c"
#include "constants.h"

//------- GLOBAL VARIABLES----------
SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;
TTF_Font * font = NULL;
int in_game = FALSE;
int status = PAUSED;
int last_frame_time = 0;


//  DATA OBJECT OF GAME
struct GRID {
    int * matrix;
    int horizontal_box;
    int vertical_box;
    int total_box;
    char details[100];
} grid;

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
            if (event.key.keysym.sym == SDLK_p) {
                status = PAUSED;
            }
            if (event.key.keysym.sym == SDLK_r) {
                status = RUNNING;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (status == PAUSED) {
                int index = (event.button.x / BLOCK_WIDTH) + (event.button.y / BLOCK_HEIGHT)*grid.horizontal_box;
                if (grid.matrix[index] == 1) {
                    grid.matrix[index] = 0;
                } else {grid.matrix[index] = 1;}
            }
    }
}

void draw_grid() {
    int total_lines_vertically = WINDOW_WIDTH / BLOCK_WIDTH;
    int total_lines_horizontally = WINDOW_HEIGHT / BLOCK_HEIGHT;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Render vertical lines

    for (int i =1; i <= total_lines_vertically; i++) {
        SDL_RenderDrawLine(renderer,  BLOCK_WIDTH * i, 0, BLOCK_WIDTH*i, WINDOW_HEIGHT);
    }

    // Render horizontal lines

    for (int i=1; i <= total_lines_horizontally; i++) {
        SDL_RenderDrawLine(renderer, 0, BLOCK_HEIGHT*i, WINDOW_WIDTH, BLOCK_HEIGHT*i);
    }


}

void draw_rectangles() {
    SDL_Rect tempbox;
    int alive = 0;
    int dead = 0;
    int x=0, y =0;
    for (int i=0; i<grid.total_box; i++) {
        if (grid.matrix[i] == 1) {
            x = i % grid.horizontal_box;
            y = i / grid.horizontal_box;
            tempbox.x = BLOCK_WIDTH*x;
            tempbox.y = BLOCK_HEIGHT*y;
            tempbox.w = BLOCK_WIDTH;
            tempbox.h = BLOCK_HEIGHT;
            SDL_SetRenderDrawColor(renderer, 47, 150, 155, 100);
            SDL_RenderFillRect(renderer, &tempbox);
            alive += 1;
        } else dead += 1;
    }
    if (status == RUNNING) sprintf(grid.details, "Alive : %d   Dead : %d   Total : %d   Status : Running ", alive, dead, grid.total_box);
    if (status == PAUSED) sprintf(grid.details, "Alive : %d  Dead : %d  Total : %d  Status : PAUSED", alive, dead, grid.total_box);
}



void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



void initialize_grid(int screen_width, int screen_height, int block_width, int block_height) {
    grid.horizontal_box = (screen_width / block_width);
    grid.vertical_box = (screen_height / block_height);
    grid.total_box = grid.horizontal_box * grid.vertical_box;
    grid.matrix = calloc(grid.total_box, sizeof(int));
}

void intialize_font() {
    if (TTF_Init() != 0) {
        fprintf(stderr,"Errpr initializing SDL_ttf \n");
        destroy_window();
    } 

    font = TTF_OpenFont(FONT, FONT_SIZE);
    if (!font) {
        fprintf(stderr, "Error loading font %s \n", TTF_GetError());
        destroy_window();
    }

}

void display_details() {
    SDL_Surface * text_surface = TTF_RenderText_Solid(font, grid.details, (SDL_Color){TEXT_COLOR_RGBA});
    SDL_Texture * text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    int text_width , text_height;
    SDL_QueryTexture(text_texture, NULL, NULL, &text_width, &text_height);
    int x = (WINDOW_WIDTH - text_width*1.2)  ;
    int y = ((WINDOW_HEIGHT+text_height*1.2) - WINDOW_HEIGHT) ;

    SDL_Rect text_rect = {x, y, text_width, text_height};
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
 }

 void render() {
    SDL_SetRenderDrawColor(renderer, 29, 26, 30, 0.8);
    SDL_RenderClear(renderer); // fills the screen with the last set color
     
    //------------ OBJECTS RENDERING BLOCK------------

    draw_rectangles();
    draw_grid();    
    display_details();
    //---------END OF OBJECTS RENDERING BLOCK---------

    SDL_RenderPresent(renderer); // switches the buffer frame
}

void manage_fps(int frame_target_time) {
    int time_to_wait = frame_target_time - (SDL_GetTicks() - last_frame_time);
    if (time_to_wait > 0 && time_to_wait <= frame_target_time) {
        SDL_Delay(time_to_wait);
    }

    last_frame_time = SDL_GetTicks();

}

int main(void) {
    in_game = initialize();
    intialize_font();
    initialize_grid(WINDOW_WIDTH, WINDOW_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT);

    while (in_game) {
        if (status == RUNNING)  grid.matrix = engine(grid.matrix, grid.total_box, grid.horizontal_box, grid.vertical_box);
        process_input();
        render();
        manage_fps(status == TRUE ? RUNNING_FRAME_TARGET_TIME : PAUSED_FRAME_TARGET_TIME);
    }
    destroy_window();
    return 0;    
}
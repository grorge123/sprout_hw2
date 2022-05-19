#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char *argv[])
{
    printf("START\n");
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }else{
        printf("SDL initialized successfully\n");
    }
    SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, 0);
 
    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
    // creates a surface to load an image into the main memory
    SDL_Surface* surface;
 
    // please provide a path for your image
    surface = IMG_Load("/home/grorge/Desktop/sprout/current/bin/0.jpeg");
    printf("Load surface %d\n", surface);
    // loads image to our graphics hardware memory.
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
 
    // clears main-memory
    SDL_FreeSurface(surface);
 
    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;
 
    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
 
    // adjust height and width of our image box.
    dest.w = 60;
    dest.h = 60;
 
    // sets initial x-position of object
    dest.x = (1000 - dest.w) / 2;
 
    // sets initial y-position of object
    dest.y = (1000 - dest.h) / 2;
 
    // controls animation loop
    int close = 0;
 
    // speed of box
    int speed = 300;
    printf("START LOOP\n");
    // animation loop
    while (!close) {
        SDL_SetRenderDrawColor( rend, 255, 0, 0, 255 );
        SDL_Event event;
        // Events management
        while (SDL_PollEvent(&event)) {
                // printf("event:%d\n", event.type);
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;
 
            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    dest.y -= speed / 30;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    dest.x -= speed / 30;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    dest.y += speed / 30;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    dest.x += speed / 30;
                    break;
                default:
                    break;
                }
            }
        }
 
        // right boundary
        if (dest.x + dest.w > 1000)
            dest.x = 1000 - dest.w;
 
        // left boundary
        if (dest.x < 0)
            dest.x = 0;
 
        // bottom boundary
        if (dest.y + dest.h > 1000)
            dest.y = 1000 - dest.h;
 
        // upper boundary
        if (dest.y < 0)
            dest.y = 0;
 
        // clears the screen
        SDL_RenderClear(rend);
        // SDL_RenderCopy(rend, tex, NULL, &dest);
        SDL_SetRenderDrawColor( rend, 0, 0, 255, 255 );
        SDL_Rect r;
        r.x = 50;
        r.y = 50;
        r.w = 50;
        r.h = 50;
        // Render rect
        SDL_RenderDrawRect(rend, &dest);
        // SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
 
        // triggers the double buffers
        // for multiple rendering
 
        // calculates to 60 fps
        TTF_Font* Sans = TTF_OpenFont("fonts/Pattaya/Pattaya-Regular.ttf", 24);

        SDL_Color White = {255, 255, 255};


        SDL_Surface* surfaceMessage =
            TTF_RenderText_Solid(Sans, "put your text here", White); 

        SDL_Texture* Message = SDL_CreateTextureFromSurface(rend, surfaceMessage);

        SDL_Rect Message_rect; //create a rect
        Message_rect.x = 50;  //controls the rect's x coordinate 
        Message_rect.y = 50; // controls the rect's y coordinte
        Message_rect.w = 100; // controls the width of the rect
        Message_rect.h = 100; // controls the height of the rect

        SDL_RenderCopy(rend, Message, NULL, &Message_rect);
        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }
    //this opens a font style and sets a size
    // destroy texture
    SDL_DestroyTexture(tex);
 
    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}
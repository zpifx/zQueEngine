#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WIDTH       640
#define HEIGHT      480

int main(int argc, char *argv[]) {
    printf("zQueEngine_V-1.0\n");

    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Could not initialize SDL2\nSDL2 Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Test", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_SOFTWARE
    );

    // Create a streaming texture
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,       // pixel format
        SDL_TEXTUREACCESS_STREAMING,    // allows CPU writes
        WIDTH, HEIGHT
    );

    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }

        void* pixels;
        int pitch;

        SDL_LockTexture(texture, NULL, &pixels, &pitch);

        uint32_t* buffer = (uint32_t*)pixels;

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                buffer[y * (pitch / 4) + x] = 0xFF0000FF;
            }
        }

        SDL_UnlockTexture(texture);

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
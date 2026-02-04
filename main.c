#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int width = 1280;
const int height = 720;
const char *title = "Image viewer";

typedef union _pixel {
    uint32_t hex;
    struct {
        uint8_t a;
        uint8_t b;
        uint8_t g;
        uint8_t r;
    } rgba;
} Pixel;

int main(int argc, char *argv[]) {
    char format[3];
    int w, h, maxColor;

    if (argc < 2) {
        printf("Uso: %s <image.ppm>\n", argv[0]);
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    if (SDL_CreateWindowAndRenderer(title, width, height, 0, &window, &renderer) < 0) return 1;

    FILE *image = fopen(argv[1], "r");
    if (!image) {
        printf("Image couldn't load.\n");
        return 1;
    }

    fscanf(image, "%s %d %d %d", format, &w, &h, &maxColor);
    Pixel *bufferColor = calloc(w * h, sizeof(Pixel));

    for (int i = 0; i < w * h; i++) {
        int r, g, b;
        if (fscanf(image, "%d %d %d", &r, &g, &b) == 3) {
            bufferColor[i].rgba.r = (uint8_t)r;
            bufferColor[i].rgba.g = (uint8_t)g;
            bufferColor[i].rgba.b = (uint8_t)b;
            bufferColor[i].rgba.a = 255;
        }
    }
    fclose(image);

    SDL_Texture *texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        w, 
        h
    );

    SDL_UpdateTexture(
        texture, 
        NULL, 
        bufferColor, 
        w * sizeof(Pixel)
    );

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) quit = true;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        
        SDL_RenderPresent(renderer);
    }

    free(bufferColor);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

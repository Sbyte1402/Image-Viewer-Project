#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <stdint.h>
#include <stdio.h>

const int width = 1280;
const int height = 720;
const char *title = "Image viewer";

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
SDL_Event event;

int main(int argc, char *argv[]){
    /*
    SDL_CreateWindowAndRenderer(
        title, 
        width, 
        height, 
        SDL_WINDOW_RESIZABLE, 
        &window, 
        &renderer
    );
    */
    
    if(argc < 2){
        printf("Expected input -> %s <image.ppm>\n", argv[0]);
        return 1;
    }

    char *image_path = argv[1];
    FILE *image = fopen(image_path, "r");

    if(!image){
        printf("Image couldn't be loaded...\n\n");
        return 1;
    }else{
        printf("Loading image: %s\n\n", image_path);
    }

    char format[3];
    int w, h, maxColor;
    
    fscanf(image, "%s", format);
    fscanf(image, "%d %d", &w, &h);
    fscanf(image, "%d", &maxColor);

    printf("File name: %s\nFormat: %s\nW|H: %d %d\nMax color: %d\n", image_path, format, w, h, maxColor);
    /*
    while(1){
        SDL_PollEvent(&event);
        if(event.type == SDL_EVENT_QUIT) break;

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    */

    return 0;
}

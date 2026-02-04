#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <assert.h>

const int width = 0;
const int height = 0;
const char *title = "Image viewer";

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
SDL_Event event;

int main(){
    SDL_CreateWindowAndRenderer(
        title, 
        width, 
        height, 
        SDL_WINDOW_RESIZABLE, 
        &window, 
        &renderer
    );
    
    while(1){
        SDL_PollEvent(&event);
        if(event.type == SDL_EVENT_QUIT) break;

        SDL_RenderPresent(renderer);
    }
    return 0;
}

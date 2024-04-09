#define main SDL_main

#include <iostream>
#include <SDL_main.h>
#include <SDL.h>
#include <SDL_events.h>

#define WIDTH 1280
#define HIGHT 720

SDL_Rect rect;

bool running, fullscreen;
int framecount, timerFps, lastframe, fps;

SDL_Renderer *renderer;
SDL_Window *window;

void update()
{
    if(fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if(!fullscreen) SDL_SetWindowFullscreen(window, 0);

    if(rect.w < 100) rect.w = WIDTH;
    if(rect.h < 100) rect.h = HIGHT;
    rect.w -=10;
    rect.h -=10;
}
void input() 
{
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT) running = false;
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        if(keystate[SDL_SCANCODE_ESCAPE]) running = false;
        if(keystate[SDL_SCANCODE_F11]) fullscreen = !fullscreen;

    }
}
void draw() 
{
    SDL_SetRenderDrawColor(renderer, 40, 43, 200, 255);
    
    rect.x = rect.y = 0;
    rect.w = WIDTH;
    rect.h = HIGHT;
    SDL_RenderFillRect(renderer, &rect);

    framecount ++;
    timerFps = SDL_GetTicks() - lastframe;
    if(timerFps < (1000/60)){
        SDL_Delay(1000/60-timerFps);

    }
    SDL_RenderPresent(renderer);
}


int main(int argc, char* argv[])
{
    running = 1;
    fullscreen =0;
    static int lastTime = 0;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cout<<"initialization failed."<<std::endl;
    if(SDL_CreateWindowAndRenderer(WIDTH, HIGHT, 0, &window, &renderer) < 0)
        std::cout<<"create window failed"<<std::endl;

    SDL_SetWindowTitle(window, "SDL2 Window");
    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    while(running){
        lastframe = SDL_GetTicks();
        if(lastframe >= (lastframe+1000)){
            lastTime = lastframe;
            fps = framecount;
            framecount = 0;
        }
        std::cout<< fps <<std::endl;


        
        input();
        draw();
        update();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}




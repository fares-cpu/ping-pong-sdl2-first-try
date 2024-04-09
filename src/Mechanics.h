//* This class holds functions easier to handle than the sdl functions, so 
//* any object from this class can be easily handled in Logic.
#include <SDL_main.h>
#include <SDL.h>
#include <iostream>

/**
 * this class makes everything with SDL easier and simpler
*/
class Initializer
{
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int screen_hight;
    int screen_width;

    Initializer(int screen_hight, int screen_width)
    {
        this->screen_hight = screen_hight;
        this->screen_width = screen_width;
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
            std::cout<<"initialization failed."<<std::endl;
        
        if(SDL_CreateWindowAndRenderer( screen_hight, screen_width, 0, &this->window, &this->renderer) < 0)
            std::cout<< "we fucked up"<<std::endl;

        SDL_SetWindowTitle(this->window, "window");
        SDL_ShowCursor(1);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    }

    void clear()
    {
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->renderer);
    }

    void destroy()
    {
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }
    
};
/**
 * Handling SDL_Rect for every Rectagle can be pain in the ass.
 * and that leads us to use objects from this class:
*/
class EasyRect
{
    public:
    SDL_Rect rect;

    int x, y;

    /**
     * @param x
     * @param y
     * @param width
     * @param hight
     * @param window
    */
    EasyRect(int x, int y, int width, int hight)
    {
        this->y = y;
        this->x = x;

        this->rect.h = hight;
        this->rect.w = width;
        this->rect.x = x;
        this->rect.y = y;
    }

    void draw(SDL_Renderer *renderer)
    {
        SDL_SetRenderDrawColor(renderer, 40, 43, 200, 255);
        SDL_RenderFillRect(renderer, &this->rect);
        SDL_RenderPresent(renderer);
    }


    void setRectX(int x)
    {
        this->x = x;
        this->rect.x = x;
    }
    void setRectY(int y)
    {
        this->y = y;
        this->rect.y = y;
    }

};
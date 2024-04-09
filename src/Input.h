//@author Knightu
//
//make sure to include this last.
#include <SDL_events.h>
#include <SDL_scancode.h>

#define NONE 0
#define GO_RIGHT 1
#define GO_LEFT  2
#define GO_UP    3
#define GO_DOWN  4

class Input
{
private:
    SDL_Event *keyEvent;
    SDL_Event event;
    Uint8 keycode;


public:
    Input()
    {

    }


    int handle()
    {
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        if(keystate[SDL_SCANCODE_UP])    return GO_UP;
        if(keystate[SDL_SCANCODE_DOWN])  return GO_DOWN;
        if(keystate[SDL_SCANCODE_RIGHT]) return GO_RIGHT;
        if(keystate[SDL_SCANCODE_LEFT])  return GO_LEFT;
        

        return NONE;
    }


    bool check_close()
    {
        while(SDL_PollEvent(&this->event)){
            if(this->event.type == SDL_QUIT)
                return true;
        }
        return false;
    }

};

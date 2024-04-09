//let's talk about our game simply and right now:
//a cube that moves....
//
#include <iostream>
#include <math.h>
#include <SDL_main.h>
#include <SDL.h>
#include <C:\Users\knightu-sama\Desktop\cpp\test-no-cmake\src\Input.h>
#include <C:\Users\knightu-sama\Desktop\cpp\test-no-cmake\src\Mechanics.h>

#define X_R 1   ///right
#define X_L 2   //left
#define Y_U 3   //up
#define Y_D 4  //down


#define B_U_R 5
#define B_U_L 6
#define B_D_R 7
#define B_D_L 8

class Game
{
private:
    Initializer *initializer;

    Input *input;

    EasyRect *player;
    EasyRect *computer;
    EasyRect *ball;

    int ball_state;




public: 
    Game()
    {
        this->init();
        int i = 0;
        while(true)
        {   
            
            this->main_loop();
            if(this->input->check_close()) {this->initializer->destroy(); break;}
            SDL_Delay(25);
        }
    }

    void init()
    {
        this->initializer = new Initializer(1280, 720);
        
        this->input = new Input();

        this->player = new EasyRect(0, 360, 25, 100);
        this->computer = new EasyRect(1255, 360, 25, 100);
        this->ball = new EasyRect(640, 360, 25, 25);
        
        this->ball_state = B_U_R;
    }

    void handle_input()
    {
        switch(this->input->handle())
        {
            case GO_UP:
                if(this->player->y > 0)
                    this->player->setRectY(this->player->y -= 10);
                break;
            case GO_DOWN:
                if(this->player->y < 620)
                    this->player->setRectY(this->player->y += 10);
                break;
            default: break;
        }
    }

    void main_loop()
    {
        this->player->draw(this->initializer->renderer);
        this->computer->draw(this->initializer->renderer);
        this->ball->draw(this->initializer->renderer);
        this->handle_input();
        this->handleBall();
        this->handleOut();
        this->initializer->clear();
    }
    int bxpps = 15;         // pixel per frame for the ball on x axis
    int bypps = 15;         //pixel per frame for the ball on y axis
    int cpps = 15;         //pixel per frame for the computer
    /**
     * 
    */
    void handleBall()
    {
        

        bool touch_computer = (
            this->ball->y >= (this->computer->y -25) 
            && this->ball->y <= (this->computer->y +100)
            && this->ball->x >= 1255
            );

        bool touch_player = (
            this->ball->y >= (this->player->y - 25)
            && this->ball->y <= (this->player->y + 100)
            && this->ball->x <= 25
        );
        int v2 = bxpps * bxpps + bypps + bypps;  // the square of the velocity of the ball
        switch(ball_state)
        {
            case B_D_R:
                if(this->ball->y >= 695) this->ball_state = B_U_R;
                if(touch_computer) 
                {
                    this->ball_state = B_U_L;
                    bypps += (this->ball->y - this->computer->y)/10;
                    // bxpps -= (this->ball->y - this->computer->y)/10;
                    bxpps = sqrt(abs(v2 - (bypps * bypps)));
                }
                break;
            case B_U_R:
                if(this->ball->y <= 0) this->ball_state = B_D_R;
                if(touch_computer)
                {
                    this->ball_state = B_D_L;
                    bypps += (this->ball->y - this->computer->y)/10;
                    // bxpps -= (this->ball->y - this->computer->y)/10;
                    bxpps = sqrt(abs(v2 - (bypps * bypps)));
                }
                break;
            case B_D_L:
                if(this->ball->y >= 695) this->ball_state = B_U_L;
                if(touch_player) 
                {
                    this->ball_state = B_U_R;
                    bypps += (this->ball->y - this->player->y)/10;
                   // bxpps -= (this->ball->y - this->player->y)/10;
                    bxpps = sqrt(abs(v2 - (bypps * bypps)));
                }
                break;
            case B_U_L:
                if(this->ball->y <= 0) this->ball_state = B_D_L;
                if(touch_player) 
                {
                    this->ball_state = B_D_R;
                    bypps += (this->ball->y - this->player->y)/10;
//                    bxpps -= (this->ball->y - this->player->y)/10;
                    bxpps = sqrt(abs(v2 - (bypps * bypps)));
                }
                break;
        }
        
        switch(ball_state)
        {
            case B_D_R:
                this->ball->setRectX(this->ball->x + bxpps);
                this->ball->setRectY(this->ball->y + bypps);
                this->computer->setRectY(this->computer->y + cpps);
                break;
            case B_U_R:
                this->ball->setRectX(this->ball->x + bxpps);
                this->ball->setRectY(this->ball->y - bypps);
                this->computer->setRectY(this->computer->y - cpps);
                break;
            case B_D_L:
                this->ball->setRectX(this->ball->x - bxpps);
                this->ball->setRectY(this->ball->y + bypps);
                this->computer->setRectY(this->computer->y + cpps);
                break;
            case B_U_L:
                this->ball->setRectX(this->ball->x - bxpps);
                this->ball->setRectY(this->ball->y - bypps);
                this->computer->setRectY(this->computer->y - cpps);
                break;
        }
    }


    void handleOut()
    {
        if(this->ball->x >= 1260 || this->ball->x <= 0)
        {
            //
            bxpps = 15;
            bypps = 15;
            this->ball->setRectX(640);
            this->ball->setRectY(360);
            this->ball_state = B_U_R;
            this->computer->setRectX(1255);
            this->computer->setRectY(360);
            this->initializer->clear();
            this->main_loop();
            SDL_Delay(2000);

            
        }
    }


};
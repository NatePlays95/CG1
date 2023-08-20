#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>

#include "source/vec3.h"
#include "source/camera.h"

using namespace std;

int WINDOW_WIDTH = 800; int WINDOW_HEIGHT = 600;
SDL_Color BACKGROUND_COLOR = {100,100,100,255};

void render_circle(SDL_Renderer * renderer, Camera camera){
    //instruções da tarefa
    
    double sphereRadius = 3;
    Vec3 spherePosition = Vec3(0,0,-15);

    const int nLin = 60; const int nCol = 80;
    SDL_Color canvas[nLin][nCol];    

    double dx = camera.frameWidth/nCol;
    double dy = camera.frameHeight/nLin;
    Ray raycast = Ray(camera.eye.position);

    srand (time(NULL));
    for (int l = 0; l < nLin; l++){
        double yj = camera.frameHeight/2 - dy/2 - l*dy;
        
        for (int c = 0; c < nCol; c++){
            double xj = -camera.frameWidth/2 + dx/2 + c*dx;

            raycast.pointTowards(Vec3(raycast.position.x + xj, raycast.position.y + yj, raycast.position.z -camera.frameDistance));
            SDL_Color resultColor;// {0,0,0,0} is transparent

            //test sphere
            double fA = raycast.direction.length_squared(); // 1
            double fB = 2 * (raycast.position - spherePosition).dot(raycast.direction);
            double fC = (raycast.position - spherePosition).length_squared() - sphereRadius*sphereRadius;
            double fD = fB*fB - 4*fA*fC; //delta

            if (fD < 0) { //nao existem raizaes
                resultColor = BACKGROUND_COLOR; //transparente
            } else {
                resultColor = {255, 0, 0, 255}; //vermelho
                
                double t;
                //nao utilizado
                if (fD == 0) { //raiz unica
                    t = -fB/fA;
                } else {
                    double t1 = (-fB + sqrt(fD)) / (2*fA);
                    double t2 = (-fB - sqrt(fD)) / (2*fA);

                    t = abs(t1)<abs(t2) ? t1 : t2;
                }
                //resultColor.r -= round(t*4);
            }

            canvas[l][c] = resultColor;
            
            //canvas[l][c] = {rand() % 256, rand() % 256, rand() % 256, 255};
        }
    }
    // Render the matrix of colors as rectangles
    int render_dx = WINDOW_WIDTH/nCol;
    int render_dY = WINDOW_HEIGHT/nLin;
    for (int l = 0; l < nLin; l++) {
        for (int c = 0; c < nCol; c++) {
            SDL_Color currentColor = canvas[l][c];
            SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);

            SDL_Rect rect = {c * render_dx, l * render_dY, render_dx, render_dY};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
};

int main(int argv, char** args)
{

    Camera camera;
    camera.frameWidth = 8;
    camera.frameHeight = 6;
    camera.frameDistance = 6;
                    //position   //direction
    camera.eye = Ray(Vec3(0,0,0), Vec3(0,0,-1));
    


    std::cout << "Hello World!\n";

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
            SDL_Keycode keyPressed = event.key.keysym.sym;
                switch (keyPressed) {
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                    case SDLK_UP:
                        camera.eye.position.z -= 0.5;
                        break;
                    case SDLK_DOWN:
                        camera.eye.position.z += 0.5;
                        break;
                    case SDLK_LEFT:
                        camera.eye.position.x -= 0.5;
                        break;
                    case SDLK_RIGHT:
                        camera.eye.position.x += 0.5;
                        break;
                    // Add more cases for other keys if needed
                }
            }
        }


        //plano de fundo
        SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
        SDL_RenderClear(renderer);
        //SDL_Rect rect = {0,0, (int)camera.frameWidth, (int)camera.frameHeight};
        //SDL_RenderFillRect(renderer, &rect);

        //draw stuff here
        render_circle(renderer, camera);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
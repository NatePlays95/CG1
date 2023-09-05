#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <list>

#include "source/camera.h"
#include "source/primitives/sphere.h"

using namespace std;

int WINDOW_WIDTH = 800; int WINDOW_HEIGHT = 600;
SDL_Color BACKGROUND_COLOR = {100,100,100,255};

void render_circle(SDL_Renderer * renderer, Camera camera, std::list<Primitive*>& renderObjectsList){
    //instruções da tarefa

    const int nLin = 60; const int nCol = 80;
    SDL_Color canvas[nLin][nCol];    

    double dx = camera.frameWidth/nCol;
    double dy = camera.frameHeight/nLin;
    Ray raycast;// = Ray(camera.eye.position);

    srand (time(NULL));
    for (int l = 0; l < nLin; l++){
        double yj = camera.frameHeight/2 - dy/2 - l*dy;
        
        for (int c = 0; c < nCol; c++){
            double xj = -camera.frameWidth/2 + dx/2 + c*dx;
            
            SDL_Color resultColor = BACKGROUND_COLOR;
            raycast = Ray(camera.eye.position);
            raycast.pointTowards(raycast.position + Vec3(xj, yj,-camera.frameDistance));

            for (auto &obj : renderObjectsList) {
                
                if (obj->intersect(raycast)) {
                    resultColor = raycast.contact_color;
                }
            }
            
            canvas[l][c] = resultColor;
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



    Sphere sphere(Vec3(0,0,-15), 3);
    sphere.color = {255, 255, 0, 255};

    Sphere sphere2(Vec3(4,0,-22), 4);
    sphere2.color = {255, 0, 0, 255};

    std::list<Primitive*> renderObjectsList;
    renderObjectsList.push_back(&sphere);
    renderObjectsList.push_back(&sphere2);

    
    std::cout << "Hello World!\n";

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
        render_circle(renderer, camera, renderObjectsList);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
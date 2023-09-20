#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <list>

#include "source/camera.h"
#include "source/primitives.h"
#include "source/lighting/pointlight.h"

using namespace std;

int WINDOW_WIDTH = 800; int WINDOW_HEIGHT = 600;
SDL_Color BACKGROUND_COLOR = {100,100,100,255};
Vec3 AMBIENT_LIGHT = Vec3(0.2,0.2,0.3);

int NLIN = 60; int NCOL = 80;


SDL_Color renderLightingStep(Ray& raycast, std::list<Light*>& renderLightsList) {
    SDL_Color resultColor = {255,255,255,255};
    Vec3 n = raycast.contact_normal;

    Vec3 eyeIntensity = Vec3(0,0,0);
    eyeIntensity = eyeIntensity + Vec3(AMBIENT_LIGHT);

    for (auto light : renderLightsList) {
        Vec3 l = (light->position - raycast.contactPosition()).normalized();
        Vec3 i = light->intensity;
        Vec3 matr = raycast.contact_material.roughness;
        Vec3 mats = raycast.contact_material.specular;
        
        Vec3 difIAtK = Vec3(i.x*matr.x, i.y*matr.y, i.z*matr.z);
        double difFactor = max(0.0, l.dot(n));
        Vec3 diffuseIntensity = difIAtK * difFactor;
        diffuseIntensity = diffuseIntensity.clampedPositive();

        eyeIntensity = eyeIntensity + diffuseIntensity;


        Vec3 specIAtK = Vec3(i.x*mats.x, i.y*mats.y, i.z*mats.z);
        Vec3 r = l.reflect(n);
        Vec3 v = raycast.direction;
        double mExp = 100; //hardness
        double specFactor = pow(max(0.0, r.dot(v)),mExp);
        Vec3 specularIntensity = specIAtK * specFactor;
        specularIntensity = specularIntensity.clampedPositive();

        eyeIntensity = eyeIntensity + specularIntensity;
    }

    eyeIntensity = (eyeIntensity * 255).floored();
    resultColor.r = clamp(eyeIntensity.x, 0.0, 255.0);
    resultColor.g = clamp(eyeIntensity.y, 0.0, 255.0);
    resultColor.b = clamp(eyeIntensity.z, 0.0, 255.0);
    return resultColor;
}

void render(SDL_Renderer * renderer, Camera camera, std::list<Shape*>& renderObjectsList, std::list<Light*>& renderLightsList){
    //instruções da tarefa

    const int nLin = 600; const int nCol = 800;
    SDL_Color canvas[nLin][nCol];    

    double dx = camera.frameWidth/nCol;
    double dy = camera.frameHeight/nLin;
    //Ray raycast;// = Ray(camera.eye.position);

    srand (time(NULL));
    for (int l = 0; l < nLin; l++){
        double yj = camera.frameHeight/2 - dy/2 - l*dy;
        
        for (int c = 0; c < nCol; c++){
            double xj = -camera.frameWidth/2 + dx/2 + c*dx;
            
            SDL_Color resultColor = BACKGROUND_COLOR;
            bool hitSomething = false;
            Ray raycast = Ray(camera.eye.position);
            raycast.pointTowards(raycast.position + Vec3(xj, yj,-camera.frameDistance));

            for (auto obj : renderObjectsList) {
                if (obj->intersect(raycast)) {
                    //resultColor = raycast.contact_color;
                    hitSomething = true;
                }
            }

            if (hitSomething) {
                resultColor = renderLightingStep(raycast, renderLightsList);
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


    PointLight* pointLight = new PointLight(Vec3(0, 50, 0), Vec3(0.7,0.7,0.7));
    // PointLight* pointLight2 = new PointLight(Vec3(10, 20, 0), Vec3(1,1,1));

    std::list<Light*> renderLightsList;
    renderLightsList.push_front(pointLight);
    // renderLightsList.push_front(pointLight2);




    Sphere* sphere = new Sphere(Vec3(0,-2,-15), 3);
    sphere->color = {255, 255, 0, 255};
    // sphere->material = Material(Vec3(0.5,0.5,0), Vec3(1,0,0));
    sphere->material = Material(Vec3(0.5,0.5,0.5), Vec3(1,1,0.7));

    Sphere* sphere2 = new Sphere(Vec3(4,0,-22), 4);
    sphere2->color = {255, 0, 0, 255};
    sphere2->material = Material(Vec3(1,0.5,1), Vec3(0,0,0.5));

    // Plane* plane = new Plane(Vec3(0,-10,0), Vec3(0,1,0));
    // plane->color = {200, 200, 200, 255};

    // Disk* disk = new Disk(Vec3(20,-10,-20), Vec3(-1,0,0), 20);
    // disk->color = {200, 200, 255, 255};

    // Cylinder* cylinder = new Cylinder(Vec3(-20, 0, -20), Vec3(1,0,-1).normalized(), 10, 20);
    // (*cylinder).setColor({200,255,200,255});

    // Cone* cone = new Cone(Vec3(4,-2,-22), Vec3(0,-1,0), 4, 8);
    // cone->setColor({255, 255, 100, 255});

    std::list<Shape*> renderObjectsList;
    renderObjectsList.push_front(sphere);
    renderObjectsList.push_front(sphere2);
    // renderObjectsList.push_front(plane);
    // renderObjectsList.push_front(disk);
    // renderObjectsList.push_front(cylinder);
    // renderObjectsList.push_front(cone);

    
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

                    case SDLK_q:
                        NLIN /= 10;
                        NCOL /= 10;
                        break;
                    case SDLK_e:
                        NLIN *= 10;
                        NCOL *= 10;
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
        render(renderer, camera, renderObjectsList, renderLightsList);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
#include <SDL2/SDL.h>
// #include <thread>
// #include <chrono>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <list>

#include "source/mat4.h"
#include "source/camera.h"
#include "source/primitives.h"
#include "source/lighting/pointlight.h"
#include "source/rendering/scene.h"

using namespace std;

int WINDOW_WIDTH = 500; int WINDOW_HEIGHT = 500;

int main(int argv, char** args)
{

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    
    SDL_Color BACKGROUND_COLOR = {100,100,100,255};
    Vec3 AMBIENT_LIGHT = Vec3(0.1,0.1,0.2);

    Camera camera;
    camera.frameWidth = 60;
    camera.frameHeight = 60;
    camera.frameDistance = 30;
    camera.lookAt(Vec3(0,0,0), Vec3(0,0,-100), Vec3(0,1,0));

    Scene scene = Scene(window, &camera, BACKGROUND_COLOR, AMBIENT_LIGHT);



    PointLight* pointLight = new PointLight(Vec3(0, 60, -30), Vec3(0.9,0.9,0.9)*5000);
    scene.addLight(pointLight);



    Sphere* sphere3 = new Sphere(Vec3(0,0,-100), 40);
    sphere3->material = Material(Vec3(1,0,0), Vec3(0.7,0.2,0.2), Vec3(0.7,0.2,0.2), 10);

    Plane* ground = new Plane(Vec3(0,-40,0), Vec3(0,1,0));
    ground->material = Material(Vec3(0.2, 0.7, 0.2), Vec3(0.2, 0.7, 0.2), Vec3(0,0,0));

    Plane* wall = new Plane(Vec3(0,0,-200), Vec3(0,0,1));
    wall->material = Material(Vec3(0.3, 0.3, 0.7), Vec3(0.3, 0.3, 0.7), Vec3(0,0,0));

    // Disk* disk = new Disk(Vec3(20,-10,-20), Vec3(-1,0,0), 20);
    // disk->color = {200, 200, 255, 255};

    // Cylinder* cylinder = new Cylinder(Vec3(-20, 0, -20), Vec3(1,0,-1).normalized(), 10, 20);
    // (*cylinder).setColor({200,255,200,255});
    // Cone* cone = new Cone(Vec3(4,-2,-22), Vec3(0,-1,0), 4, 8);
    // cone->setColor({255, 255, 100, 255});

    scene.addShape(sphere3);
    scene.addShape(ground);
    scene.addShape(wall);



    scene.run();

    return 0;
}
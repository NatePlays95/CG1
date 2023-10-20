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
#include "source/mesh/wrappedmesh.h"
#include "source/transformations.h"

using namespace std;

int WINDOW_WIDTH = 500; int WINDOW_HEIGHT = 500;

int main(int argv, char** args)
{

    //Mesh objCube = Mesh::loadFromFileObj("cube");

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Color BACKGROUND_COLOR = {100,100,100,255};
    Vec3 AMBIENT_LIGHT = Vec3(0.5,0.5,0.5);

    Camera camera;
    camera.frameWidth = 60;
    camera.frameHeight = 60;
    camera.frameDistance = 30;
    camera.lookAt(Vec3(0,0,0), Vec3(0,0,-100), Vec3(0,1,0));

    Scene scene = Scene(window, renderer, &camera, BACKGROUND_COLOR, AMBIENT_LIGHT);
    //Scene scene = Scene(window, &camera, BACKGROUND_COLOR, AMBIENT_LIGHT);



    PointLight* pointLight = new PointLight(Vec3(0, 60, -30), Vec3(0.9,0.9,0.9)*5000);
    scene.addLight(pointLight);
    PointLight* pointLight2 = new PointLight(Vec3(0, 60, -100), Vec3(0.9,0.9,0.4)*1000);
    scene.addLight(pointLight2);

    Sphere* sphereLight = new Sphere(Vec3(0, 60, -30), 10);
    sphereLight->material = Material(Vec3(1,0,0), Vec3(0.7,0.2,0.2), Vec3(0.7,0.2,0.2), 10);    

    Sphere* sphere3 = new Sphere(Vec3(0,0,-100), 40);
    sphere3->material = Material(Vec3(1,0,0), Vec3(0.7,0.2,0.2), Vec3(0.7,0.2,0.2), 10);

    Plane* ground = new Plane(Vec3(0,-40,0), Vec3(0,1,0));
    ground->material = Material(Vec3(0.2, 0.7, 0.2), Vec3(0.2, 0.7, 0.2), Vec3(0,0,0));

    Plane* wall = new Plane(Vec3(0,0,-200), Vec3(0,0,1));
    wall->material = Material(Vec3(0.3, 0.3, 0.7), Vec3(0.3, 0.3, 0.7), Vec3(0,0,0));

    //40/3.0
    Cylinder* cylinder = new Cylinder(Vec3(0,0,-100), Vec3(-1,1,-1).normalized(), 40/3.0, 120);
    cylinder->setMaterial(Material(Vec3(0.2, 0.3, 0.8),Vec3(0.2, 0.3, 0.8),Vec3(0.2, 0.3, 0.8)));

    Vec3 conePos = Vec3(0,0,-100) + Vec3(-1,1,-1).normalized()*60;
    Cone* cone = new Cone(conePos, Vec3(-1,1,-1).normalized(), 60, 20);
    cone->setMaterial(Material(Vec3(0.8, 0.3, 0.2),Vec3(0.8, 0.3, 0.2),Vec3(0.8, 0.3, 0.2)));

    Cone* cone2 = new Cone(Vec3(40,-40,-100), Vec3(0,1,0).normalized(), 40, 80);
    cone2->setMaterial(Material(Vec3(0.8, 0.3, 0.2),Vec3(0.8, 0.3, 0.2),Vec3(0.8, 0.3, 0.2)));

    WrappedMesh* objCube = new WrappedMesh();
    objCube->loadFromFileObj("cube");
    objCube->applyTransform(Transformations::scale(20,20,20));
    objCube->applyTransform(Transformations::translate(0,0,-100));
    objCube->material = Material(Vec3(0.2, 0.7, 0.2), Vec3(0.2, 0.7, 0.2), Vec3(0,0,0));
    // Load a BMP image
    SDL_Surface* imageSurface = SDL_LoadBMP("assets/textures/dirt.bmp");
    if (!imageSurface) {
        SDL_Log("Failed to load image: %s", SDL_GetError());
    } else {  // Create a texture from the image surface
        SDL_Texture * texDirt = SDL_CreateTextureFromSurface(renderer, imageSurface);
        objCube->material.texture = texDirt;
    }
    
    WrappedMesh* objCube2 = new WrappedMesh();
    objCube2->loadFromFileObj("cube");
    objCube2->applyTransform(Transformations::scale(10,10,10));
    objCube2->applyTransform(Transformations::translate(0,20,-110));
    objCube2->material = Material(Vec3(0.2, 0.3, 0.8),Vec3(0.2, 0.3, 0.8),Vec3(0.2, 0.3, 0.8));
    
    // scene.addShape(sphereLight);
    // scene.addShape(sphere3);
    scene.addShape(ground);
    scene.addShape(wall);
    scene.addShape(objCube);
    scene.addShape(objCube2);
    // scene.addShape(cylinder);
    scene.addShape(cone);
    // scene.addShape(cone2);

    scene.run();

    return 0;
}
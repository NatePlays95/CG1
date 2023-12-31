#include <SDL2/SDL.h>
// #include <thread>
// #include <chrono>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <list>
#include "source/mat4.h"
#include "source/camera.h"
#include "source/primitives/primitives.h"
#include "source/lighting/lighting.h"
#include "source/rendering/scene.h"
#include "source/mesh/wrappedmesh.h"
#include "source/mesh/compositemesh.h"
#include "source/transformations.h"

using namespace std;
const double PI  = 3.141592653589793238463;
int WINDOW_WIDTH = 1000; int WINDOW_HEIGHT = 1000;


int main(int argv, char** args)
{
    
    SDL_Init(SDL_INIT_EVERYTHING);
    int imgFlags = IMG_INIT_PNG;  // Initialize support for PNG images (or other formats).
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        // Handle SDL_image initialization error.
    }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Build();

    SDL_Window *window = SDL_CreateWindow("Hello SDL!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGuiSDL::Initialize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    // ImGui_ImplSDL2_NewFrame();

    SDL_Color BACKGROUND_COLOR = {200,230,255,255};
    Vec3 AMBIENT_LIGHT = Vec3(0.4,0.6,0.7);

    Camera camera;
    camera.frameWidth = 60;
    camera.frameHeight = 60;
    camera.frameDistance = 50;
    // Zoom
    // camera.setFOV(PI/2.0 + PI/4.0); //135°
    // camera.setFOV(PI/2.0); //90°
    camera.setFOV(PI/3.0); //60°
    camera.lookAt(Vec3(1164,181,1038), Vec3(1164,181,1038)+Vec3(1,-0.5,1).normalized(), Vec3(0,1,0));

    Scene scene = Scene(window, renderer, &camera, BACKGROUND_COLOR, AMBIENT_LIGHT);

    Material city1 = Material(Vec3(0.95,1,1), Vec3(0.95,1,1)*0.8, Vec3(1,1,1)*0.6, 10);
    Material city2 = Material(Vec3(0.95,1,0.9)*0.6, Vec3(0.95,1,0.9)*0.4, Vec3(0.9,0.9,1)*0.6, 100);



    Plane* water = new Plane(Vec3(0,100,0), Vec3(0,1,0));
    water->material = Material(Vec3(1,1,1), Vec3(1,1,1), Vec3(1,1,1)*0.3, 100);
    water->material.texture = new Texture("water");
    scene.addShape(water);

    Cylinder* road = new Cylinder(Vec3(1900,75,1055), Vec3(1,0,0), 80, 2000);
    road->setMaterial(Material(Vec3(0.4,0.2,0.7), Vec3(0.4,0.2,0.7), Vec3(1,1,1)*0.1, 10));
    scene.addShape(road);

    Cylinder* building1 = new Cylinder(Vec3(1700,120,1800), Vec3(0,1,0), 60, 200);
    building1->setMaterial(city2);
    scene.addShape(building1);
    Cylinder* building2 = new Cylinder(Vec3(1500,150,1900), Vec3(0,1,0), 60, 240);
    building2->setMaterial(city1);
    scene.addShape(building2);
    Cylinder* building3 = new Cylinder(Vec3(1220,150,1800), Vec3(0,1,0), 80, 200);
    building3->setMaterial(city2);
    scene.addShape(building3);
    Cylinder* building4 = new Cylinder(Vec3(1850,100,1400), Vec3(0,1,0), 130, 150);
    building4->setMaterial(city1);
    scene.addShape(building4);

    Sphere* towerBase = new Sphere(Vec3(1500,50,1500), 100);
    towerBase->material = city1;
    Cone* towerBody = new Cone(Vec3(1500,120,1500), Vec3(0,1,0), 40, 200);
    towerBody->setMaterial(city1);
    CompositeShape* tower = new CompositeShape();
    tower->name = "tower";
    tower->addShape(towerBase);
    tower->addShape(towerBody);
    scene.addShape(tower);

    Sphere* tower2bot = new Sphere(Vec3(1900, 250, 1700), 70);
    Sphere* tower2top = new Sphere(Vec3(1900, 330, 1700), 70);
    Cylinder* tower2base = new Cylinder(Vec3(1900, 150, 1700), Vec3(0,1,0), 50, 100);
    tower2base->setMaterial(city2);
    CompositeShape* tower2 = new CompositeShape();
    tower2->name = "tower2";
    tower2->addShape(tower2base); tower2->addShape(tower2bot); tower2->addShape(tower2top);
    tower2->setMaterial(city2);
    scene.addShape(tower2);


    WrappedMesh* blueFalcon = new WrappedMesh();
    blueFalcon->loadFromFileObj("blue_falcon_fixed");
    blueFalcon->material = Material(Vec3(1,1,1), Vec3(1,1,1), Vec3(1,1,1), 100);
    blueFalcon->material.texture = new Texture("blue_falcon");
    blueFalcon->applyTransform(Transformations::rotateY(PI*1.04));
    blueFalcon->applyTransform(Transformations::rotateX(PI*0.2));
    blueFalcon->applyTransform(Transformations::translate(1300,154,1080));
    scene.addShape(blueFalcon);

    SpotLight* lamp = new SpotLight(Vec3(1269,160,1082), Vec3(1,1,1)*50000000, Vec3(-1,-1,-0.3).normalized(), PI*0.4);
    scene.addLight(lamp);

    // PointLight* pt = new PointLight(Vec3(1100,150,1080), Vec3(1,1,1)*100000);
    // scene.addLight(pt);
    // PointLight* pt2 = new PointLight(Vec3(1269,153,1082), Vec3(1,1,1)*1000000);
    // scene.addLight(pt2);
    // Sphere* pointLightSource = new Sphere(Vec3(1269,153,1082), 5);
    // scene.addShape(pointLightSource);

    DirectionalLight* sun = new DirectionalLight(Vec3(0,0,0), Vec3(1,1,1)*2, Vec3(0.7,-0.2,-0.4).normalized());
    scene.addLight(sun);


    scene.run();

    return 0;
}
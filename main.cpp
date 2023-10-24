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

    SDL_Color BACKGROUND_COLOR = {100,100,100,255};
    Vec3 AMBIENT_LIGHT = Vec3(0.5,0.5,0.5);

    Camera camera;
    // camera.frameWidth = 60;
    // camera.frameHeight = 60;
    camera.frameDistance = 50;
    camera.setFOV(PI/2.0); //90°
    // camera.setFOV(PI/3.0);
    camera.lookAt(Vec3(0,40,0), Vec3(0,-30,-100), Vec3(0,1,0));

    Scene scene = Scene(window, renderer, &camera, BACKGROUND_COLOR, AMBIENT_LIGHT);
    //Scene scene = Scene(window, &camera, BACKGROUND_COLOR, AMBIENT_LIGHT);



    // PointLight* pointLight = new PointLight(Vec3(0, 60, -30), Vec3(0.9,0.9,0.9)*5000);
    // scene.addLight(pointLight);
    // SpotLight* spotLight = new SpotLight(Vec3(0, 60, -70), Vec3(0.9,0.9,0.9)*5000, (Vec3(0, 60, -70)*-1 + Vec3(0,0,0)).normalized(), PI/3.0);
    // scene.addLight(spotLight);
    DirectionalLight* sun = new DirectionalLight(Vec3(0, 0, 0), Vec3(0.9,0.9,0.6)*5, Vec3(0,-1,5).normalized());
    scene.addLight(sun);

    Sphere* sphereLight = new Sphere(Vec3(0, 60, -30), 10);
    sphereLight->material = Material(Vec3(1,0,0), Vec3(0.7,0.2,0.2), Vec3(0.7,0.2,0.2), 10);    

    Sphere* sphere3 = new Sphere(Vec3(0,0,-100), 40);
    sphere3->material = Material(Vec3(1,0,0), Vec3(0.7,0.2,0.2), Vec3(0.7,0.2,0.2), 10);

    Plane* ground = new Plane(Vec3(0,0,0), Vec3(0,1,0));
    ground->material = Material(Vec3(0.2, 0.7, 0.2), Vec3(0.2, 0.7, 0.2), Vec3(0,0,0));

    Plane* wall = new Plane(Vec3(0,0,-200), Vec3(0,0,1));
    wall->material = Material(Vec3(0.3, 0.3, 0.7), Vec3(0.3, 0.3, 0.7), Vec3(0,0,0));

    Cylinder* cylinder = new Cylinder(Vec3(0,0,-100), Vec3(-1,1,-1).normalized(), 40/3.0, 120);
    cylinder->setMaterial(Material(Vec3(0.2, 0.3, 0.8),Vec3(0.2, 0.3, 0.8),Vec3(0.2, 0.3, 0.8)));

    Vec3 conePos = Vec3(0,0,-100) + Vec3(-1,1,-1).normalized()*60;
    Cone* cone = new Cone(conePos, Vec3(-1,1,-1).normalized(), 60, 20);
    cone->setMaterial(Material(Vec3(0.8, 0.3, 0.2),Vec3(0.8, 0.3, 0.2),Vec3(0.8, 0.3, 0.2)));

    Cone* cone2 = new Cone(Vec3(40,-40,-100), Vec3(0,1,0).normalized(), 40, 80);
    cone2->setMaterial(Material(Vec3(0.2, 0.2, 0.2),Vec3(1, 1, 1),Vec3(0.3, 0.3, 0.3), 10));

    // WrappedMesh* objCube = new WrappedMesh();
    // objCube->loadFromFileObj("cube");
    // objCube->applyTransform(Transformations::scale(20,20,20));
    // objCube->applyTransform(Transformations::translate(0,0,-100));
    // objCube->material = Material(Vec3(0.2, 0.2, 0.2),Vec3(1, 1, 1),Vec3(0.3, 0.3, 0.3), 10);
    // Texture* texDirt = new Texture("dirt");
    // objCube->material.texture = texDirt;

    // WrappedMesh* objCar = new WrappedMesh();
    // objCar->loadFromFileObj("s15");
    // objCar->applyTransform(Transformations::scale(20,20,20));
    // objCar->applyTransform(Transformations::translate(20,-20, 0));
    // objCar->material = Material(Vec3(0.2, 0.2, 0.2),Vec3(1, 1, 1),Vec3(0.3, 0.3, 0.3), 10);
    // Texture* texCar = new Texture("s15_base_color");
    // objCar->material.texture = texCar;

    WrappedMesh* objBlueFalcon = new WrappedMesh();
    objBlueFalcon->loadFromFileObj("blue_falcon_fixed");
    objBlueFalcon->applyTransform(Transformations::scale(1,1,1));
    // objBlueFalcon->applyTransform(Transformations::rotateZAroundPoint(PI/3.0, Vec3(-20,0,0)));
    objBlueFalcon->recalculateBounds();
    objBlueFalcon->applyTransform(Transformations::translate(0,0,0));
    objBlueFalcon->material = Material(Vec3(1, 1, 1),Vec3(1, 1, 1),Vec3(0.7, 0.8, 1), 100);
    Texture* texBlueFalcon = new Texture("blue_falcon");
    objBlueFalcon->material.texture = texBlueFalcon;
    
    // WrappedMesh* objCube2 = new WrappedMesh();
    // objCube2->loadFromFileObj("cube");
    // objCube2->applyTransform(Transformations::scale(5,50,5));
    // objCube2->applyTransform(Transformations::translate(0,20,-110));
    // objCube2->material = Material(Vec3(0.2, 0.3, 0.8),Vec3(0.2, 0.3, 0.8),Vec3(0.2, 0.3, 0.8));

    // WrappedMesh* objGorila = new WrappedMesh();
    // objGorila->loadFromFileObj("gorila");
    // // objGorila->applyTransform(Transformations::scale(5,50,5));
    // objGorila->applyTransform(Transformations::translate(0,0,0));
    // objGorila->material = Material(Vec3(0.7, 0.3, 0.8),Vec3(0.7, 0.3, 0.8),Vec3(1, 1, 1));
    
    // scene.addShape(sphereLight);
    // scene.addShape(sphere3);
    scene.addShape(ground);
    // scene.addShape(wall);
    // scene.addShape(objCube);
    // scene.addShape(objCar);
    scene.addShape(objBlueFalcon);
    // scene.addShape(objGorila);
    // scene.addShape(cylinder);
    // scene.addShape(cone);
    // scene.addShape(cone2);

    scene.run();

    return 0;
}
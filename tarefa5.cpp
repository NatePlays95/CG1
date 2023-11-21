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
    Vec3 AMBIENT_LIGHT = Vec3(0.3,0.3,0.3);

    Camera camera;
    camera.frameWidth = 60;
    camera.frameHeight = 60;
    camera.frameDistance = 50;
    camera.setFOV(PI/2.0); //90°
    // camera.setFOV(PI/3.0);
    camera.lookAt(Vec3(0,0,0), Vec3(0,-30,-100), Vec3(0,1,0));

    Scene scene = Scene(window, renderer, &camera, BACKGROUND_COLOR, AMBIENT_LIGHT);

    Vec3 color1 = Vec3(0.686, 0.933, 0.933);
    Vec3 color2 = Vec3(0.933,0.933,0.933);
    Vec3 color3 = Vec3(0.824, 0.706, 0.549);
    Vec3 color4 = Vec3(0., 1., 0.498);
    Vec3 color5 = Vec3(0.854, 0.647, 0.125);
    Vec3 color6 = Vec3(1., 0.078, 0.576);

    Material matWood = Material(Vec3(0,0,0), Vec3(0,0,0), Vec3(0.2,0.2,0.2), 1);
    matWood.texture = new Texture("wood");
    Material mat1 = Material(color1, color1, color1, 5);
    Material mat2 = Material(color2, color2, color2);
    Material mat3 = Material(color3, color3, color3);
    Material mat4 = Material(color4, color4, color4);
    Material mat5 = Material(color5, color5, color5);
    Material mat6 = Material(color6, color6, color6);




    Plane* ground = new Plane(Vec3(0,-150,0),Vec3(0,1,0));
    ground->material = matWood;
    
    Plane* wallR = new Plane(Vec3(200,-150,0),Vec3(-1,0,0));
    wallR->material = mat1;

    Plane* wallF = new Plane(Vec3(200,-150,-400),Vec3(0,0,1));
    wallF->material = mat1;

    Plane* wallL = new Plane(Vec3(-200,-150,0),Vec3(1,0,0));
    wallL->material = mat1;

    Plane* ceiling = new Plane(Vec3(0,150,0), Vec3(0,-1,0));
    ceiling->material = mat2;

    Cylinder* cylinder = new Cylinder(Vec3(0,-150+45, -200), Vec3(0,1,0), 5, 90);
    cylinder->setMaterial(mat3);

    Cone* cone = new Cone(Vec3(0,-60, -200), Vec3(0,1,0), 90, 150);
    cone->setMaterial(mat4);

    WrappedMesh* objCube = new WrappedMesh();
    objCube->loadFromFileObj("cube");
    objCube->applyTransform(Transformations::scale(20,20,20)); //arestas tem tamanho 2 por padrão
    objCube->applyTransform(Transformations::translate(0,-150+20,-165));
    objCube->material = mat6;
    // Texture* texDirt = new Texture("dirt");
    // objCube->material.texture = texDirt;
    WrappedMesh* objCube2 = new WrappedMesh();
    objCube2->loadFromFileObj("cube_uvtest");
    // objCube2->applyTransform(Transformations::rotateY(PI));
    objCube2->applyTransform(Transformations::scale(20,20,20)); //arestas tem tamanho 2 por padrão
    objCube2->applyTransform(Transformations::translate(-50,-150+20,-165));
    objCube2->material = mat6;
    Texture* texPresent = new Texture("uv_test");
    objCube2->material.texture = texPresent;

    Sphere* sphere = new Sphere(Vec3(0,95,-200), 5);
    sphere->material = mat5;


    scene.addShape(ground);
    // scene.addShape(wallR);
    // scene.addShape(wallF);
    // scene.addShape(wallL); 
    // scene.addShape(ceiling);
    // scene.addShape(cylinder);
    // scene.addShape(cone);
    scene.addShape(objCube);
    scene.addShape(objCube2);
    // scene.addShape(sphere);

    PointLight* lightP = new PointLight(Vec3(-100,140,-20), Vec3(0.7,0.7,0.7)*10000);

    scene.addLight(lightP);


        

    


    scene.run();

    return 0;
}
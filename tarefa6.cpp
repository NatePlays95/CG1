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

    SDL_Color BACKGROUND_COLOR = {100,100,100,255};
    Vec3 AMBIENT_LIGHT = Vec3(0.3,0.3,0.3);

    Camera camera;
    camera.frameWidth = 60;
    camera.frameHeight = 60;
    camera.frameDistance = 50;
    camera.setFOV(PI/2.0); //90°
    // camera.setFOV(PI/3.0);
    camera.lookAt(Vec3(0,100,100), Vec3(0,-30,-100), Vec3(0,1,0));

    Scene scene = Scene(window, renderer, &camera, BACKGROUND_COLOR, AMBIENT_LIGHT);


    Plane* ground = new Plane(Vec3(0,0,0),Vec3(0,1,0));
    ground->material = Material(Vec3(0.5, 0.5, 0.5), Vec3(0.5, 0.5, 0.5), Vec3(0.5, 0.5, 0.5));
    // ground->material.texture = new Texture("wood");

    Sphere* sphere = new Sphere(Vec3(0,95,-200), 5);

    scene.addShape(sphere);
    scene.addShape(ground);



    Material matTable = Material(Vec3(0.5, 0.5, 0.5), Vec3(0.5, 0.5, 0.5), Vec3(0.5, 0.5, 0.5));
    matTable.texture = new Texture("wood");

    WrappedMesh* objTableTop = new WrappedMesh();
    objTableTop->loadFromFileObj("cube");
    objTableTop->applyTransform(Transformations::scale(125,2.5,75)); //arestas tem tamanho 2 por padrão
    objTableTop->applyTransform(Transformations::translate(0, 95 + 2.5, 0));
    objTableTop->material = matTable;
    WrappedMesh* objTableLeg1 = new WrappedMesh();
    objTableLeg1->loadFromFileObj("cube");
    objTableLeg1->applyTransform(Transformations::scale(2.5,95/2.0,75));
    objTableLeg1->applyTransform(Transformations::translate(125 - 2.5,95/2.0, 0));
    objTableLeg1->material = matTable;
    WrappedMesh* objTableLeg2 = new WrappedMesh();
    objTableLeg2->loadFromFileObj("cube");
    objTableLeg2->applyTransform(Transformations::scale(2.5,95/2.0,75));
    objTableLeg2->applyTransform(Transformations::translate(-125 + 2.5,95/2.0, 0));
    objTableLeg2->material = matTable;
    CompositeMesh* table = new CompositeMesh();
    table->addMesh(objTableTop);
    table->addMesh(objTableLeg1);
    table->addMesh(objTableLeg2);
    table->applyTransform(Transformations::translate(0,0,-200));
    // table->applyTransform(Transformations::scale(0.5,0.5,0.5));
    // objTableTop->applyTransform(Transformations::scale(0.5,0.5,0.5));
    // objTableLeg1->applyTransform(Transformations::scale(0.5,0.5,0.5));
    // objTableLeg2->applyTransform(Transformations::scale(0.5,0.5,0.5));

    scene.addShape(table);


    Cone* treeLeaves = new Cone(Vec3(0,49,0), Vec3(0,1,0), 60, 150);
    treeLeaves->setMaterial(Material(Vec3(0,0.7,0),Vec3(0,0.7,0),Vec3(0,0,0), 1));

    Sphere* treeStar = new Sphere(Vec3(0,49+150+4.5,0), 4.5);
    Cylinder* treeTrunk = new Cylinder(Vec3(0, 9+20, 0), Vec3(0,1,0), 6, 40);
    Cylinder* treeBase = new Cylinder(Vec3(0, 4.5, 0), Vec3(0,1,0), 30, 9);
    CompositeShape* tree = new CompositeShape();
    tree->addShape(treeLeaves);
    tree->addShape(treeStar);
    tree->addShape(treeTrunk);
    tree->addShape(treeBase);

    scene.addShape(tree);



    PointLight* lightP = new PointLight(Vec3(-100,140,-20), Vec3(0.7,0.7,0.7)*10000);

    scene.addLight(lightP);


        

    


    scene.run();

    return 0;
}
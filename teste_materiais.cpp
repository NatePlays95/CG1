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
    camera.lookAt(Vec3(0,0,100), Vec3(0,-30,-100), Vec3(0,1,0));

    Scene scene = Scene(window, renderer, &camera, BACKGROUND_COLOR, AMBIENT_LIGHT);

    // DirectionalLight* sun = new DirectionalLight(Vec3(0,0,0), Vec3(1,1,1)*2, Vec3(0.5,-0.5,0).normalized());
    // scene.addLight(sun);
                                       //posição       //intensidade
    PointLight* light = new PointLight(Vec3(0,1,0), Vec3(0.7,0.7,0.7)*10000);
    scene.addLight(light);

    // Material mat1 = Material(Vec3(0,0,0), Vec3(0,0,0), Vec3(1,1,1), 2);
    // Material mat2 = Material(Vec3(0,0,0), Vec3(0,0,0), Vec3(1,1,1), 10);
    // Material mat3 = Material(Vec3(0,0,0), Vec3(0,0,0), Vec3(1,1,1), 50);
    // Material mat4 = Material(Vec3(0,0,0), Vec3(0,0,0), Vec3(1,1,1), 250);
    // Material mat5 = Material(Vec3(0,0,0), Vec3(0,0,0), Vec3(1,1,1), 1250);
    Material dif = Material(Vec3(0.95,1,1), Vec3(0.95,1,1)*0.8, Vec3(1,1,1)*0.6, 10);

    // Sphere* s1 = new Sphere(Vec3(0,0,0), 50); s1->material = mat1;
    // Sphere* s2 = new Sphere(Vec3(200,0,0), 50); s2->material = mat2;
    // Sphere* s3 = new Sphere(Vec3(400,0,0), 50); s3->material = mat3;
    // Sphere* s4 = new Sphere(Vec3(600,0,0), 50); s4->material = mat4;
    // Sphere* s5 = new Sphere(Vec3(800,0,0), 50); s5->material = mat5;

    Sphere* s1 = new Sphere(Vec3(100,0,0), 40); s1->material = dif;
    Sphere* s2 = new Sphere(Vec3(000,0,200), 40); s2->material = dif;
    Sphere* s3 = new Sphere(Vec3(-300,0,0), 40); s3->material = dif;
    Sphere* s4 = new Sphere(Vec3(0,0,-400), 40); s4->material = dif;
    // Sphere* s5 = new Sphere(Vec3(800,0,0), 40); s5->material = dif;

    scene.addShape(s1);
    scene.addShape(s2);
    scene.addShape(s3);
    scene.addShape(s4);
    // scene.addShape(s5);

    // WrappedMesh* blueFalcon = new WrappedMesh();
    // blueFalcon->loadFromFileObj("blue_falcon_fixed");
    // blueFalcon->material = Material(Vec3(1,1,1), Vec3(1,1,1), Vec3(1,1,1), 100);
    // blueFalcon->material.texture = new Texture("blue_falcon");
    // // blueFalcon->applyTransform(Transformations::rotateY(PI*1.04));
    // // blueFalcon->applyTransform(Transformations::rotateX(PI*0.2));
    // // blueFalcon->applyTransform(Transformations::translate(1300,154,1080));
    // scene.addShape(blueFalcon);
    
    scene.run();

    return 0;
}
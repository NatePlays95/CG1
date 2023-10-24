#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl2.h"
#include "../imgui/imgui_sdl.h"
// #include "../imgui/imgui_impl_win32.h"
#include <list>
#include <vector>
#include <cmath>
// #include <future>
#include <thread>
#include <numbers>
#include "../vec3.h"
#include "../camera.h"
#include "../lighting/light.h"
#include "../shape.h"


using namespace std;

class Scene {
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;
        
        SDL_Color backgroundColor = {100,100,100,255};
        Vec3 ambientLight = Vec3(0.2,0.2,0.2);

        Camera camera;

        std::list<Light*> lightsList;
        std::list<Shape*> shapesList;

        int canvasLines = 50; int canvasColumns = 50;
        std::vector<std::vector<SDL_Color>> canvas;

        std::vector<std::thread *> renderWorkers;
        std::vector<bool> renderWorkersFinished;
        
        bool isRunning = false;


        int mouseLastX = 0;
        int mouseLastY = 0;
        bool mouseLeftPressed = false;

        bool forwardPressed = false;
        bool backwardPressed = false;
        bool upPressed = false;
        bool downPressed = false;
        bool leftPressed = false;
        bool rightPressed = false;

        //Scene(SDL_Window * window_in, Camera * camera_in, SDL_Color background={100,100,100,255}, Vec3 ambientLight=Vec3(0.2,0.2,0.2));
        Scene(SDL_Window * window_in, SDL_Renderer * renderer_in, Camera * camera_in, SDL_Color background={100,100,100,255}, Vec3 ambientLight=Vec3(0.2,0.2,0.2));
        ~Scene(); 

        int run();

        void handleInput();
        void updateCameraRotation(int mouseX, int mouseY);

        void render();
        bool isRenderWorkersAllFinished();
        void paintCanvas();
        void paintCanvasAsync();
        void paintCanvasNewThread();
        void paintLine(int l);
        void paintQuadrant(int startL, int endL, int startC, int endC);
        void paintPixel(int l, int c);
        void drawCanvasToWindow(std::vector<std::vector<SDL_Color>> * canvas_in);

        void addLight(Light * light_in);
        void addShape(Shape * shape_in);

        SDL_Color getLightColorAt(Ray &raycast);
};

#endif
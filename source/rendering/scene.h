#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>

#include <list>
#include <vector>
#include "../vec3.h"
#include "../camera.h"
#include "../lighting/light.h"
#include "../shape.h"


using namespace std;

class Scene{
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;
        
        SDL_Color backgroundColor = {100,100,100,255};
        Vec3 ambientLight = Vec3(0.2,0.2,0.2);

        Camera camera;

        std::list<Light*> lightsList;
        std::list<Shape*> shapesList;

        int canvasLines = 100; int canvasColumns = 100;
        std::vector<std::vector<SDL_Color>> canvas;
        
        bool isRunning = false;


        int mouseLastX = 0;
        int mouseLastY = 0;
        bool mouseLeftPressed = false;


        bool upPressed = false;
        bool downPressed = false;
        bool leftPressed = false;
        bool rightPressed = false;

        Scene(SDL_Window * window_in, Camera * camera_in, SDL_Color background={100,100,100,255}, Vec3 ambientLight=Vec3(0.2,0.2,0.2));
        ~Scene(); 

        void initialize();
        int run();

        void handleInput();
        void updateCameraRotation(int mouseX, int mouseY);

        void render();
        void paintCanvas(std::vector<std::vector<SDL_Color>> * canvas_in);
        void drawCanvasToWindow(std::vector<std::vector<SDL_Color>> * canvas_in);

        void addLight(Light * light_in);
        void addShape(Shape * shape_in);

        SDL_Color getLightColorAt(Ray &raycast);
};

#endif
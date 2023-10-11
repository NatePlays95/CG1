#include "scene.h"
#include <algorithm>

Scene::~Scene() {
    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

Scene::Scene(SDL_Window * window_in, Camera * camera_in, SDL_Color background_in, Vec3 ambientLight_in) {
    backgroundColor = background_in;
    ambientLight = ambientLight_in;
    camera = *camera_in;

    window = window_in;
    initialize();
};

void Scene::initialize() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {}

    //
};

int Scene::run() {
    isRunning = true;
    while (isRunning) {
        handleInput();

        float deltaTime = 0.016f; // Example time step (adjust as needed)
        //update(deltaTime);
        render();
    }

    return 0;
};



void Scene::handleInput() {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            SDL_Keycode keyPressed = event.key.keysym.sym;
            switch (keyPressed) {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                case SDLK_UP:
                    upPressed = true;
                    break;
                case SDLK_DOWN:
                    downPressed = true;
                    break;
                case SDLK_LEFT:
                    leftPressed = true;
                    break;
                case SDLK_RIGHT:
                    rightPressed = true;
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            SDL_Keycode keyReleased = event.key.keysym.sym;
            switch (keyReleased) {
                case SDLK_UP:
                    upPressed = false;
                    break;
                case SDLK_DOWN:
                    downPressed = false;
                    break;
                case SDLK_LEFT:
                    leftPressed = false;
                    break;
                case SDLK_RIGHT:
                    rightPressed = false;
                    break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            // Handle mouse button click event
        }
    }

    if (upPressed) {
        camera.position.z -= 2;
        camera.lookAt(camera.position, camera.target, Vec3(0,1,0));
    }
    if (downPressed) {
        camera.position.z += 2;
        camera.lookAt(camera.position, camera.target, Vec3(0,1,0));
    }
    if (leftPressed) {
        camera.position.x -= 2;
        camera.lookAt(camera.position, camera.target, Vec3(0,1,0));
    }
    if (rightPressed) {
        camera.position.x += 2;
        camera.lookAt(camera.position, camera.target, Vec3(0,1,0));
    }
};


void Scene::render() {
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderClear(renderer);
    
    //draw all 3d shapes
    canvas.resize(canvasLines, std::vector<SDL_Color>(canvasColumns));
    paintCanvas(&canvas);

    //now draw to screen
    drawCanvasToWindow(&canvas);


    SDL_RenderPresent(renderer);
};





void Scene::paintCanvas(std::vector<std::vector<SDL_Color>> * canvas_in) {
    double dx = camera.frameWidth / canvasColumns;
    double dy = camera.frameHeight / canvasLines;

    for (int l = 0; l < canvasLines; l++){
        double yj = -camera.frameHeight/2 + dy/2 + l*dy;
        
        for (int c = 0; c < canvasColumns; c++){
            double xj = -camera.frameWidth/2 + dx/2 + c*dx;
            
            Mat4 cameraToWorld = camera.cameraToWorldMatrix();

            SDL_Color resultColor;// = backgroundColor;
            bool hitSomething = false;
            Ray raycast = Ray(camera.position);
            
            //TODO: swap to using matrices.
            Vec3 targetScreenPos = camera.position;
            targetScreenPos = targetScreenPos + camera.k * -camera.frameDistance;
            targetScreenPos = targetScreenPos + camera.i * xj;
            targetScreenPos = targetScreenPos + camera.j * yj;
            
            raycast.pointTowards(targetScreenPos);

            for (auto obj : shapesList) {
                if (obj->intersect(raycast)) {
                    //resultColor = raycast.contact_color;
                    hitSomething = true;
                }
            }

            if (hitSomething) {
                resultColor = getLightColorAt(raycast);
            } else {
                resultColor = backgroundColor;
            }

            canvas[l][c] = resultColor;
        }
    }
};

SDL_Color Scene::getLightColorAt(Ray& raycast) {
    SDL_Color resultColor = {255,255,255,255};
    Vec3 eyeIntensity = Vec3(0,0,0);

    Vec3 mata = raycast.contact_material.ambient;
    Vec3 ambientIntensity = Vec3(ambientLight.x*mata.x, ambientLight.y*mata.y, ambientLight.z*mata.z);

    eyeIntensity = eyeIntensity + ambientIntensity;
    
    for (auto light : lightsList) {
        Vec3 l = (light->position - raycast.contactPosition()).normalized();

        //test for shadows
        Ray shadowRaycast = Ray(light->position, l * (-1));
        bool raycastHit = false;
        bool isShadow = false;
        double renderContactDistance = (light->position - raycast.contactPosition()).mag();
        for (auto obj : shapesList) {
            raycastHit = obj->intersect(shadowRaycast) || raycastHit;

            if (raycastHit && shadowRaycast.t < renderContactDistance - 0.00000001){ //sombra
                isShadow = true;
                break;
            }
        }

        if (isShadow) break; //sai do loop das luzes
        
        eyeIntensity = eyeIntensity + light->calculateHitIntensity(&raycast);
    }

    eyeIntensity = (eyeIntensity * 255).floored();
    resultColor.r = clamp(eyeIntensity.x, 0.0, 255.0);
    resultColor.g = clamp(eyeIntensity.y, 0.0, 255.0);
    resultColor.b = clamp(eyeIntensity.z, 0.0, 255.0);
    return resultColor;
}

void Scene::drawCanvasToWindow(std::vector<std::vector<SDL_Color>> * canvas_in) {
    int render_dx = SDL_GetWindowSurface(window)->w / canvasColumns;
    int render_dY = SDL_GetWindowSurface(window)->h / canvasLines;
    
    for (int l = 0; l < canvasLines; l++) {
        for (int c = 0; c < canvasColumns; c++) {
            SDL_Color currentColor = canvas[l][c];
            SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);

            SDL_Rect rect = {c * render_dx, l * render_dY, render_dx, render_dY};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
};


void Scene::addLight(Light * light_in) {
    lightsList.push_front(light_in);
};


void Scene::addShape(Shape * shape_in) {
    shapesList.push_front(shape_in);
};




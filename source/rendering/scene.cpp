#include "scene.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include "../transformations.h"

Scene::~Scene() {
    // Clean up resources
    // ImGui_ImplWin32_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

Scene::Scene(SDL_Window * window_in, SDL_Renderer * renderer_in, Camera * camera_in, SDL_Color background_in, Vec3 ambientLight_in) {
    backgroundColor = background_in;
    ambientLight = ambientLight_in;
    camera = *camera_in;
    renderer = renderer_in;
    window = window_in;

    SDL_GetRendererOutputSize(renderer, &mouseLastX, &mouseLastY);
    mouseLastX /= 2; mouseLastY /= 2;

    canvas.resize(SDL_GetWindowSurface(window)->h, std::vector<SDL_Color>(SDL_GetWindowSurface(window)->w));

    renderWorkersFinished = std::vector<bool>(canvasLines*canvasColumns, true);;
};



int Scene::run() {
    isRunning = true;

    while (isRunning) {
        // ImGui_ImplWin32_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(&isRunning);

        // ImGuiSDL::Render(ImGui::GetDrawData());

        handleInput();

            time_t start, end;
            time(&start);
        render();
            time(&end);
            double time_taken = double(end-start);
            // cout << "time taken for render: " << time_taken << "s" << endl;

        
        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    for (auto worker : renderWorkers) {
        (*worker).join();
    }
    return 0;
};



void Scene::handleInput() {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);

        if (event.type == SDL_QUIT) {
            isRunning = false;
        } 

        //mouse
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouseLeftPressed = true;
            mouseLastX = event.button.x; mouseLastY = event.button.y;
            if (shiftPressed) {
                pick(mouseLastX, mouseLastY);
            }
        }
        else if (event.type == SDL_MOUSEBUTTONUP) {
            mouseLeftPressed = false;
        }

        else if (event.type == SDL_MOUSEMOTION) {
            // Update camera rotation based on mouse movement
            if (mouseLeftPressed) {
                updateCameraRotation(event.motion.x, event.motion.y);
            }
        } 
        
        else if (event.type == SDL_KEYDOWN) {
            SDL_Keycode keyPressed = event.key.keysym.sym;
            switch (keyPressed) {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                case SDLK_UP:
                    forwardPressed = true;
                    break;
                case SDLK_w:
                    forwardPressed = true;
                    break;
                case SDLK_DOWN:
                    backwardPressed = true;
                    break;
                case SDLK_s:
                    backwardPressed = true;
                    break;
                case SDLK_LEFT:
                    leftPressed = true;
                    break;
                case SDLK_a:
                    leftPressed = true;
                    break;
                case SDLK_RIGHT:
                    rightPressed = true;
                    break;
                case SDLK_d:
                    rightPressed = true;
                    break;
                case SDLK_q:
                    upPressed = true;
                    break;
                case SDLK_e:
                    downPressed = true;
                    break;
                case SDLK_LSHIFT:
                    shiftPressed = true;
                    break;
                case SDLK_o:
                    canvasColumns = min(canvasColumns+50, 500);
                    break;
                case SDLK_i:
                    canvasColumns = max(canvasColumns-50, 50);
                    break;
                case SDLK_l:
                    canvasLines = min(canvasLines+50, 500);
                    break;
                case SDLK_k:
                    canvasLines = max(canvasLines-50, 50);
                    break;
                case SDLK_r:
                    if (canvasLines >= 500 && canvasColumns >= 500) {
                        canvasLines = 50; canvasColumns = 50;
                    } else {
                        canvasLines = 500; canvasColumns = 500;
                    }
                    break;
            }
        } 
        else if (event.type == SDL_KEYUP) {
            SDL_Keycode keyReleased = event.key.keysym.sym;
            switch (keyReleased) {
                case SDLK_UP:
                    forwardPressed = false;
                    break;
                case SDLK_w:
                    forwardPressed = false;
                    break;
                case SDLK_DOWN:
                    backwardPressed = false;
                    break;
                case SDLK_s:
                    backwardPressed = false;
                    break;
                case SDLK_LEFT:
                    leftPressed = false;
                    break;
                case SDLK_a:
                    leftPressed = false;
                    break;
                case SDLK_RIGHT:
                    rightPressed = false;
                    break;
                case SDLK_LSHIFT:
                    shiftPressed = false;
                    break;
                case SDLK_d:
                    rightPressed = false;
                    break;
                case SDLK_q:
                    upPressed = false;
                    break;
                case SDLK_e:
                    downPressed = false;
                    break;
            }
        }
    }

    int moveSpeed = 1;

    if (forwardPressed) {
        Vec3 up = Vec3(0,1,0);
        Vec3 forward = (camera.k - (camera.k).projectOnto(up)).normalized()*-1;
        camera.position = camera.position + forward*moveSpeed;
        camera.target = camera.target + forward*moveSpeed;
        camera.lookAt(camera.position, camera.target, Vec3(0,1,0));
    }
    if (backwardPressed) {
        Vec3 up = Vec3(0,1,0);
        Vec3 forward = (camera.k - (camera.k).projectOnto(up)).normalized()*-1;
        camera.position = camera.position - forward*moveSpeed;
        camera.target = camera.target - forward*moveSpeed;
        camera.lookAt(camera.position, camera.target, Vec3(0,1,0));
    }
    if (leftPressed) {
        camera.position = camera.position + camera.i*moveSpeed*-1;
        camera.target = camera.target + camera.i*moveSpeed*-1;
        camera.lookAt(camera.position, camera.target, Vec3(0,1,0));
    }
    if (rightPressed) {
        camera.position = camera.position - camera.i*moveSpeed*-1;
        camera.target = camera.target - camera.i*moveSpeed*-1;
        camera.lookAt(camera.position, camera.target, Vec3(0,1,0));
    }
    if (upPressed) {
        camera.position = camera.position + Vec3(0,1,0)*moveSpeed;
        camera.target = camera.target + Vec3(0,1,0)*moveSpeed;
        camera.lookAt(camera.position, camera.target, Vec3(0,1,0));
    }
    if (downPressed) {
        camera.position = camera.position - Vec3(0,1,0)*moveSpeed;
        camera.target = camera.target - Vec3(0,1,0)*moveSpeed;
        camera.lookAt(camera.position, camera.target, Vec3(0,1,0));
    }
};


//placeholder, moving the camera around
void Scene::updateCameraRotation(int mouseX, int mouseY) {
    double mouseSensitivity = 0.3;
 
    double deltaX = (mouseX-mouseLastX)*mouseSensitivity/100.0;
    double deltaY = (mouseY-mouseLastY)*mouseSensitivity/100.0;

    //look left/right: rotate around world Y axis
    camera.target = (Transformations::rotateYAroundPoint(-deltaX, camera.position) * Vec4(camera.target)).to3();

    // Vec3 moveVec = Vec3(-deltaX, deltaY, 0.0)*mouseSensitivity; //should we multiply with cameraToWorld?
    camera.lookAt(camera.position, camera.target, Vec3(0,1,0));

    //look up/down: rotate around camera J axis
    camera.target = (Transformations::rotateAroundAxis(deltaY, camera.i, camera.position) * Vec4(camera.target)).to3();

    camera.lookAt(camera.position, camera.target, Vec3(0,1,0));

    mouseLastX = mouseX; mouseLastY = mouseY;
};



void Scene::render() {
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderClear(renderer);
    
    //draw all 3d shapes
    // paintCanvas();
    paintCanvasNewThread();
    // if (isRenderWorkersAllFinished()) {
        // paintCanvasAsync();
    // };
    
    //now draw to screen
    drawCanvasToWindow(&canvas);
    SDL_RenderPresent(renderer);
};


bool Scene::isRenderWorkersAllFinished() {
    bool result = true;
    for (int i = 0; i < renderWorkersFinished.size(); i++) {
        if (renderWorkersFinished[i] == false) {
            result = false; break;
        }
    }
    return result;
}

void Scene::paintCanvas() {
    // renderWorkers.clear();
    // renderWorkersFinished = std::vector<bool>(canvasLines*canvasColumns, true);;

    for (int l = 0; l < canvasLines; l++){
        for (int c = 0; c < canvasColumns; c++){
            paintPixel(l, c);
        }
    }

};

void Scene::paintCanvasNewThread() {
    if (!isRenderWorkersAllFinished()) return;

    // renderWorkers.clear();
    renderWorkersFinished = std::vector<bool>(1, false);;

    std::thread* myThread = new std::thread([this]() {
        while(this->isRunning) {
            for (int l = 0; l < canvasLines; l++){
                for (int c = 0; c < canvasColumns; c++){
                    paintPixel(l, c);
                }
            }
        }
        //this->renderWorkersFinished[0] = true;
    }); 
    renderWorkers.push_back(myThread);
    // renderWorkers[0]->join();
};

void Scene::paintCanvasAsync() {
    renderWorkers.clear();
    renderWorkersFinished = std::vector<bool>(canvasLines*canvasColumns, false);;
    int columnsCount = canvasColumns;

    for (int l = 0; l < 2; l++){
        for (int c = 0; c < 2; c++) {

            // std::thread* myThread = new std::thread([this, l, columnsCount]() {
            //     this->paintLine(l);
            //     for (int a = 0; a < columnsCount; a++) {
            //         this->renderWorkersFinished[l*columnsCount + a] = true;
            //     }
            // }); 
            std::thread* myThread = new std::thread([this, l, c]() {
                this->paintQuadrant(
                    (l)*canvasLines/2, (l+1)*canvasLines/2,
                    (c)*canvasColumns/2, (c+1)*canvasColumns/2);
                // for (int a = (c)*canvasColumns/2; a < (c+1)*canvasColumns; a++) {
                    // this->renderWorkersFinished[c*canvasColumns + a] = true;
                // }
            }); 
            renderWorkers.push_back(myThread);

        }
    }

    // for (int i = 0; i < renderWorkers.size(); i++) {
        // renderWorkers[i]->join();
    // }
};

void Scene::paintLine(int l) {
    for (int c = 0; c < canvasColumns; c++){
        paintPixel( l,  c);
    }
}

void Scene::paintQuadrant(int startL, int endL, int startC, int endC) {
    for (int l = startL; l < endL; l++){
        for (int c = startC; c < endC; c++){
            paintPixel( l,  c);
        } 
    }
}


void Scene::paintPixel(int l, int c) {
    double dx = camera.frameWidth / canvasColumns;
    double dy = camera.frameHeight / canvasLines;
    double frameY = camera.frameHeight/2 - dy/2 - l*dy;
    double frameX = -camera.frameWidth/2 + dx/2 + c*dx;
    SDL_Color resultColor;// = backgroundColor;
    bool hitSomething = false;
    Ray raycast = Ray(camera.position);

    //TODO: swap to using matrices.
    Vec3 targetScreenPos = camera.position;
    targetScreenPos = targetScreenPos + camera.k * -camera.frameDistance;
    targetScreenPos = targetScreenPos + camera.i * frameX;
    targetScreenPos = targetScreenPos + camera.j * frameY;

    raycast.pointTowards(targetScreenPos);

    for (auto obj : shapesList) {
        if (obj->intersect(raycast)) {
            hitSomething = true;
        }
    }

    if (hitSomething) {
        resultColor = getLightColorAt(raycast);
    } else {
        resultColor = backgroundColor;
    }

    canvas[l][c] = resultColor;
};

SDL_Color Scene::getLightColorAt(Ray& raycast) {
    SDL_Color resultColor = {255,255,255,255};
    Vec3 eyeIntensity = Vec3(0,0,0);

    Vec3 mata = raycast.contact_material.ambient;
    if (raycast.contact_material.texture != nullptr) {
        mata = raycast.contact_material.getDiffuseAtUV(renderer, raycast.contact_uv);
    }
    Vec3 ambientIntensity = Vec3(ambientLight.x*mata.x, ambientLight.y*mata.y, ambientLight.z*mata.z);

    eyeIntensity = eyeIntensity + ambientIntensity;
    
    for (auto light : lightsList) {
        Vec3 l = light->getLVector(raycast.contactPosition()).normalized();

        //test for shadows
        double margin = 0.0001;

        // Ray shadowRaycast = Ray(light->position, l*(-1));
        // bool raycastHit = false;
        // bool isShadow = false;
        // double renderContactDistance = light->getIncidenceDistance(raycast.contactPosition());
        // for (auto obj : shapesList) {
        //     raycastHit = obj->intersect(shadowRaycast) || raycastHit;       
        //     // if (shadowRaycast.t < margin) {//hits ray origin point
        //     //     raycastHit = false;
        //     //     continue;
        //     // }; 
        //     if (raycastHit && shadowRaycast.t+margin < renderContactDistance){ //sombra
        //         isShadow = true;
        //         break;
        //     }
        // }

        Ray shadowRaycast = Ray(raycast.contactPosition() + l*margin, l);
        // Ray shadowRaycast = Ray(raycast.contactPosition(), l);
        bool raycastHit = false;
        bool isShadow = false;
        double renderContactDistance = light->getIncidenceDistance(raycast.contactPosition());
        for (auto obj : shapesList) {
            raycastHit = obj->intersect(shadowRaycast) || raycastHit;       
            // if (shadowRaycast.t < margin) {//hits ray origin point
            //     raycastHit = false;
            //     continue;
            // }; 
            if (raycastHit && shadowRaycast.t+margin < renderContactDistance){ //sombra
                isShadow = true;
                break;
            }
        }

        if (isShadow) continue; //vai pra proxima luz
        
        eyeIntensity = eyeIntensity + light->calculateHitIntensity(renderer, &raycast);
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
            // SDL_Color currentColor = canvas[l][canvasColumns-1-c];
            SDL_Color currentColor = canvas[l][c];
            SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);

            SDL_Rect rect = {c * render_dx, l * render_dY, render_dx, render_dY};
            SDL_RenderFillRect(renderer, &rect);

            // SDL_RenderPresent(renderer);
        }
    }
};

void Scene::pick(int mouseX, int mouseY) {
    // int l = mouseY * canvasLines / SDL_GetWindowSurface(window)->h;
    // int c = mouseX * canvasColumns / SDL_GetWindowSurface(window)->w;
    double dx = camera.frameWidth / canvasColumns;
    double dy = camera.frameHeight / canvasLines;
    double ddx = mouseX * camera.frameWidth / 1000.0;
    double ddy = mouseY * camera.frameHeight / 1000.0;
    //l = mouseX / 1000; c = mouseY / 1000;
    double frameY = camera.frameHeight/2 - dy/2 - ddy;
    double frameX = -camera.frameWidth/2 + dx/2 + ddx;
    // double frameX = camera.frameWidth/2 - dx/2 - ddx;
    Shape* hitShape = nullptr;
    bool hitSomething = false;
    Ray raycast = Ray(camera.position);

    //TODO: swap to using matrices.
    Vec3 targetScreenPos = camera.position;
    targetScreenPos = targetScreenPos + camera.k * -camera.frameDistance;
    targetScreenPos = targetScreenPos + camera.i * frameX;
    targetScreenPos = targetScreenPos + camera.j * frameY;

    raycast.pointTowards(targetScreenPos);

    for (auto obj : shapesList) {
        if (obj->intersect(raycast)) {
            hitSomething = true;
            hitShape = obj;
        }
    }

    cout << "- Pick at X:" << mouseX << " Y:" << mouseY << " hit distance " << raycast.t << endl;
    if (hitSomething) hitShape->printToConsole();
    cout << endl;
};


void Scene::addLight(Light * light_in) {
    lightsList.push_front(light_in);
};


void Scene::addShape(Shape * shape_in) {
    shapesList.push_front(shape_in);
};
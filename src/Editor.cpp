#include "Core/Input.hpp"
#include "DynamicScriptLoader.hpp"
#include "FileManager.hpp"
#include "Graphics/GL/Graphics.hpp"
#include "Window/Window.hpp"
#include <Editor.hpp>
#include <iostream>


// Creating pointers of required classes
Window *E_window;
Graphics *E_graphics;
Input *E_input;
FileManager *E_filemanager;
DynamicScriptLoader *E_dynamicSL;

// if true the update functions of scripts will run
bool isPlaying = false;

// A input call back funciton
// give your input code here for only once keycall
void InputCallBacks(GLFWwindow *window, int key, int scancode, int action,
                    int mods) {
    if (key == INPUT_KEY_R && action == INPUT_PRESS) {
        std::cerr << "R Pressed\n";
        E_dynamicSL->DSLReload();
    }
    if(key == INPUT_KEY_P && action == INPUT_PRESS){
        // if isplaying is true -> sets to false
        // if isplaying is false -> sets to true
        isPlaying = !isPlaying;
    }
}

// called at the start of Editor
void Editor::PreInit() {
    // getting all required classes instances
    E_window = E_window->WGetInstance();
    E_graphics = E_graphics->GGetInstance();
    E_input = E_input->IGetInstance();
    E_filemanager = E_filemanager->FMGetInstance();
    E_dynamicSL = E_dynamicSL->DSLGetInstance();

    // search for shared objects in the projects scripts/so directory
    E_filemanager->SearchSharedObjects();

    // load found shared objects
    E_dynamicSL->DSLLoad();
}

// Actual Editor init
// Application level functions are called here
void Editor::Init() {
    // glfw init
    E_window->WInitGLFW();
    // create window
    E_window->WCreateWindow();
    // set created window to current context
    E_window->WSetContext();
    E_window->WEnableKeyCallBack = true;
    E_window->WSetCallback(InputCallBacks);
    // Init Input
    E_input->IInit();

    // load gl lib
    E_graphics->GInit();
    // set viewport size
    E_graphics->GSetViewPort(0, 0, 800, 800);
}
// user level init
// scripts init function will be called here
void Editor::PostInit() { E_dynamicSL->DSLRunInit(); }
void Editor::PreStart() {}
// user level start
// scripts start function will be called here
void Editor::Start() { E_dynamicSL->DSLRunStart(); }
void Editor::PostStart() {}

void Editor::Update() {
    // if ALT+ESC is pressed the editor will Close/Exit
    if (E_input->IGetKeyDown(INPUT_KEY_LEFT_ALT)) {
        if (E_input->IGetKeyDown(INPUT_KEY_ESCAPE)) {
            E_window->WExitWindow();
        }
    }
    if(E_dynamicSL->isRecompiled){
        E_dynamicSL->DSLRunInit();
        E_dynamicSL->DSLRunStart();
        E_dynamicSL->isRecompiled = false;
    }
    if (isPlaying) {
        // Runs Scripts update function
        E_dynamicSL->DSLRunUpdate();
    }

    // polling window events
    E_window->WPollEvents();
    // set BG color
    E_graphics->GBackGroundColor(0.35, 0.45, 0.55, 1.0);
    // update window
    E_window->WUpdate();
    E_window->WSwapBuffers();
}
// user level exit
// scripts exit function will be called here
void Editor::preExit() { E_dynamicSL->DSLRunExit(); }
void Editor::Exit() {
    // destroy window
    E_window->WDestroyWindow();
    // terminate glfw
    E_window->WExitGLFW();
}
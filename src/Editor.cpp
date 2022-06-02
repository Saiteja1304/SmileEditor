#include "CScriptManager.hpp"
#include "Core/Input.hpp"
#include "FileManager.hpp"
#include "Graphics/GL/Graphics.hpp"
#include "Window/Window.hpp"
#include <Editor.hpp>
#include <iostream>

// Creating pointers of required classes
Window &E_window = E_window.WGetInstance();
Graphics& E_graphics = E_graphics.GGetInstance();
Input &E_input = E_input.IGetInstance();
FileManager &E_filemanager = E_filemanager.FMGetInstance();
CScriptManager &E_cscriptmanager = E_cscriptmanager.CSMGetInstance();

// if true the update functions of scripts will run
bool isPlaying = false;

// A input call back funciton
// give your input code here for only once keycall
void InputCallBacks(GLFWwindow *window, int key, int scancode, int action,
                    int mods) {
                        if(key == INPUT_KEY_P && action == INPUT_PRESS){
                            isPlaying = !isPlaying;
                        }
                    }

// called at the start of Editor
void Editor::PreInit() {
    // search for shared objects in the projects scripts/so directory
    E_filemanager.SearchSharedObjects();
    // load Scripts
    E_cscriptmanager.CSMLoadScripts();
}

// Actual Editor init
// Application level functions are called here
void Editor::Init() {
    // glfw init
    E_window.WInitGLFW();
    // create window
    E_window.WCreateWindow();
    // set created window to current context
    E_window.WSetContext();
    E_window.WEnableKeyCallBack = true;
    E_window.WSetCallback(InputCallBacks);
    // Init Input
    E_input.IInit();

    // load gl lib
    E_graphics.GInit();
    // set viewport size
    E_graphics.GSetViewPort(0, 0, 800, 800);
}
// user level init
// scripts init function will be called here
void Editor::PostInit() { E_cscriptmanager.CSMScriptInit(); }
void Editor::PreStart() {}
// user level start
// scripts start function will be called here
void Editor::Start() {}
void Editor::PostStart() { E_cscriptmanager.CSMScriptStart(); }

void Editor::Update() {
    // if ALT+ESC is pressed the editor will Close/Exit
    if (E_input.IGetKeyDown(INPUT_KEY_LEFT_ALT)) {
        if (E_input.IGetKeyDown(INPUT_KEY_ESCAPE)) {
            E_window.WExitWindow();
        }
    }
    // Script update function
    {
        if (isPlaying) {
            E_cscriptmanager.CSMScriptUpdate();
        }
    }
    // polling window events
    E_window.WPollEvents();
    // set BG color
    // E_graphics.GBackGroundColor(0.35, 0.45, 0.55, 1.0);
    // update window
    E_window.WUpdate();
    E_window.WSwapBuffers();
}
// user level exit
// scripts exit function will be called here
void Editor::preExit() { E_cscriptmanager.CSMScriptExit(); }
void Editor::Exit() {
    // destroy window
    E_window.WDestroyWindow();
    // terminate glfw
    E_window.WExitGLFW();
}
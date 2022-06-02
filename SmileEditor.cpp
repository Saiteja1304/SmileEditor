// Graphics Header from Smile Lib
#include <Graphics/GL/Graphics.hpp>
// Window Header from Smile Lib
#include <Window/Window.hpp>
// Input Header from Smile Lib
#include <Core/Input.hpp>
#include <Core/Group.hpp>
// Smile Editor Main Header
#include <SmileEditor.hpp>

// std
#include <iostream>

// Set Singleton class's instance to 0
Editor *Editor::EInstance = 0;
Window *Window::WInstance = 0;
Graphics *Graphics::GInstance = 0;
Input *Input::IInstance = 0;
FileManager *FileManager::FMInstance = 0;
// GroupManager* GroupManager::GMInstance = 0;

int main(int argc, char *argv[]) {

    // Get window and graphics instances
    Editor *editor = editor->EGetInstance();
    Window *window = window->WGetInstance();
    // if args count is less that two
    // the second argument should be location of projects root directory
    if (argc < 2) {
        std::cerr << "No arguments passed to exectable...\nPlease add project "
                     "location as the first argument\n";
        return 0;
    } else {
        // setting projects root directory
        editor->ProjectRootLoc = argv[1];
        // setting scripts directory
        editor->ScriptsLoc = editor->ProjectRootLoc + "Scripts/";
        // setting shared objects directory in scripts folder
        editor->SOLoc = editor->ScriptsLoc + "SO/";
    }
    // Editors PreInit function
    editor->PreInit();
    // Editors Init function
    editor->Init();
    // Editors PostInit function
    editor->PostInit();
    // Editors PreStart function
    editor->PreStart();
    // Editors Start function
    editor->Start();
    // Editors PostStart function
    editor->PostStart();
    // main loop
    while (window->WIsRunning) {
        // Editors Update function 
        editor->Update();
    }
    // Editors PreExit function
    editor->preExit();
    // Editors Exit function
    editor->Exit();

    return 0;
}
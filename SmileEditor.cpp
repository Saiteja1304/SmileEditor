// Graphics Header from Smile Lib
#include "CScriptManager.hpp"
#include <Graphics/GL/Graphics.hpp>
// Window Header from Smile Lib
#include <Window/Window.hpp>
// Input Header from Smile Lib
#include <Core/Group.hpp>
#include <Core/Input.hpp>
// Smile Editor Main Header
#include <SmileEditor.hpp>

// std
#include <iostream>

int main(int argc, char *argv[]) {

    // Get window and graphics instances
    Editor &editor = editor.EGetInstance();
    Window &window = window.WGetInstance();
    // if args count is less that two
    // the second argument should be location of projects root directory
    if (argc < 2) {
        std::cerr << "No arguments passed to exectable...\nPlease add project "
                     "location as the first argument\n";
        return 0;
    } else {
        // setting projects root directory
        editor.ProjectRootLoc = argv[1];
        // setting scripts directory
        editor.ScriptsLoc = editor.ProjectRootLoc + "Scripts/";
        // setting shared objects directory in scripts folder
        editor.SOLoc = editor.ScriptsLoc + "SO/";
    }
    // Editors PreInit function
    editor.PreInit();
    // Editors Init function
    editor.Init();
    // Editors PostInit function
    editor.PostInit();
    // Editors PreStart function
    editor.PreStart();
    // Editors Start function
    editor.Start();
    // Editors PostStart function
    editor.PostStart();
    // main loop
    while (window.WIsRunning) {
        // Editors Update function
        editor.Update();
    }
    // Editors PreExit function
    editor.preExit();
    // Editors Exit function
    editor.Exit();

    return 0;
}
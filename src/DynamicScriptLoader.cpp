#include <DynamicScriptLoader.hpp>
#include <dlfcn.h>
#include <iostream>
#include <string.h>

void DynamicScriptLoader::__GetFunctions() {
    for (int i = 0; i < scriptptrs.size(); i++) {
        scriptptrs[i].handle = dlopen(
            (DSLFM->FMEditor->SOLoc + "/" + scriptptrs[i].scriptName).c_str(),
            RTLD_NOW);
        if (scriptptrs[i].handle == NULL) {
            std::cerr << "Cannot open shared object "
                      << scriptptrs[i].scriptName << "[Error]" << dlerror()
                      << "\n";
        } else {
            std::cerr << "Opened " << scriptptrs[i].scriptName << "\n";
        }
        scriptptrs[i].Init =
            reinterpret_cast<void (*)()>(dlsym(scriptptrs[i].handle, "Init"));
        if (scriptptrs[i].Init == NULL) {
            std::cerr << "Failed to obtained init"
                      << "[error] " << dlerror() << '\n';
        }
        scriptptrs[i].Start =
            reinterpret_cast<void (*)()>(dlsym(scriptptrs[i].handle, "Start"));
        if (scriptptrs[i].Start == NULL) {
            std::cerr << "Failed to obtained Start"
                      << "[error] " << dlerror() << '\n';
        }
        scriptptrs[i].Update =
            reinterpret_cast<void (*)()>(dlsym(scriptptrs[i].handle, "Update"));
        if (scriptptrs[i].Update == NULL) {
            std::cerr << "Failed to obtained Update"
                      << "[error] " << dlerror() << '\n';
        }
        scriptptrs[i].Exit =
            reinterpret_cast<void (*)()>(dlsym(scriptptrs[i].handle, "Exit"));
        if (scriptptrs[i].Exit == NULL) {
            std::cerr << "Failed to obtained Exit"
                      << "[error] " << dlerror() << '\n';
        }
    }
}
void DynamicScriptLoader::__GetScripts() {
    for (int i = 0; i < DSLFM->SharedObjects.size(); i++) {
        ScriptPtr tempscrpt;
        strcpy(tempscrpt.scriptName, DSLFM->SharedObjects[i].c_str());
        scriptptrs.push_back(tempscrpt);
    }
}

void DynamicScriptLoader::DSLLoad() {
    _DestroyScripts();
    _CheckForSharedObjects();
    __GetScripts();
    __GetFunctions();
}
void DynamicScriptLoader::DSLReload() {
    _DestroyScripts();
    _CheckForSharedObjects();
    __GetScripts();
    __GetFunctions();
    isRecompiled = true;
}
void DynamicScriptLoader::DSLRunInit() {
    for (int i = 0; i < scriptptrs.size(); i++) {
        scriptptrs[i].Init();
    }
}
void DynamicScriptLoader::DSLRunStart() {
    for (int i = 0; i < scriptptrs.size(); i++) {
        scriptptrs[i].Start();
    }
}
void DynamicScriptLoader::DSLRunUpdate() {
    for (int i = 0; i < scriptptrs.size(); i++) {
        scriptptrs[i].Update();
    }
}
void DynamicScriptLoader::DSLRunExit() {
    for (int i = 0; i < scriptptrs.size(); i++) {
        scriptptrs[i].Exit();
    }
}
void DynamicScriptLoader::DSLDestroy() { _DestroyScripts(); }
void DynamicScriptLoader::_DestroyScripts() {
    if (scriptptrs.size() > 0) {
        for (int i = 0; i < scriptptrs.size(); i++) {
            dlclose(scriptptrs[i].handle);
        }
        scriptptrs.clear();
    }
}
void DynamicScriptLoader::_CheckForSharedObjects() {
    DSLFM->SearchSharedObjects();
}
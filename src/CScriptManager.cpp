#include "Scripting/CScript.hpp"
#include <CScriptManager.hpp>
#include <dlfcn.h>
#include <iostream>

void CScriptManager::__loadScripts() {
    for (int i = 0; i < CSM_filemanager.SharedObjects.size(); i++) {
        scripts[i].handle = dlopen(
            (CSM_editor.SOLoc + CSM_filemanager.SharedObjects[i]).c_str(),
            RTLD_NOW);
        if (scripts[i].handle == NULL) {
            std::cerr << "failed to open shared object " << dlerror()
                      << CSM_filemanager.SharedObjects[i] << "\n";
        } else {
            scripts[i].GetPtr = reinterpret_cast<CScript *(*)()>(
                dlsym(scripts[i].handle, "GetPtr"));
            if (scripts[i].GetPtr == NULL) {
                std::cerr << "Function Not found\n";
            } else {
                std::cerr << "Found getptr function\n";
                scripts[i].script = scripts[i].GetPtr();
            }
        }
    }
}
void CScriptManager::__closehandles() {
    unsigned short int size = CSM_filemanager.SharedObjects.size();
    for (int i = 0; i < size; i++) {
        dlclose(scripts->handle);
    }
}

void CScriptManager::CSMLoadScripts() {
    // allocate memory
    scripts = new struct_scripts[CSM_filemanager.SharedObjects.size()];
    // call load scripts function
    __loadScripts();
}

void CScriptManager::CSMReloadScripts() {
    // call destructor
    // close handles
    __closehandles();
    // deallocate memory
    delete[] scripts;
    // load scripts
    CSMLoadScripts();
    isReCompiled = true;
}
void CScriptManager::CSMDestroyScripts() {
    // call destructor
    // close handles
    __closehandles();
    // deallocate memory
    delete[] scripts;
}

void CScriptManager::CSMScriptInit() {
    for (int i = 0; i < CSM_filemanager.SharedObjects.size(); i++) {
        scripts[i].script->Init();
    }
}
void CScriptManager::CSMScriptStart() {
    for (int i = 0; i < CSM_filemanager.SharedObjects.size(); i++) {
        scripts[i].script->Start();
    }
}
void CScriptManager::CSMScriptUpdate() {
    for (int i = 0; i < CSM_filemanager.SharedObjects.size(); i++) {
        scripts[i].script->Update();
    }
}
void CScriptManager::CSMScriptExit() {
    for (int i = 0; i < CSM_filemanager.SharedObjects.size(); i++) {
        scripts[i].script->Exit();
    }
}

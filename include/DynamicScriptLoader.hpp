#ifndef DYNAMICSCRIPTLOADER_HPP
#define DYNAMICSCRIPTLOADER_HPP
// #include "SmileEditor.hpp"
#include "Editor.hpp"
#include "FileManager.hpp"
#include <vector>
struct ScriptPtr {
    bool isInitiated = false;
    char scriptName[15];
    void *handle;
    void (*Init)();
    void (*Start)();
    void (*Update)();
    void (*Exit)();
};
class DynamicScriptLoader {
  public:
    FileManager *DSLFM = DSLFM->FMGetInstance();
    std::vector<ScriptPtr> scriptptrs;
    static DynamicScriptLoader *DSLInstance;
    static DynamicScriptLoader *DSLGetInstance() {
        if (!DSLInstance)
            DSLInstance = new DynamicScriptLoader;
        return DSLInstance;
    }
    bool isRecompiled = false;
    void DSLLoad();
    void DSLReload();
    void DSLRunUpdate();
    void DSLRunStart();
    void DSLRunInit();
    void DSLRunExit();
    void DSLDestroy();

  private:
    void __GetFunctions();
    void __GetScripts();
    void _CheckForSharedObjects();
    void _DestroyScripts();
    DynamicScriptLoader() {}
    ~DynamicScriptLoader() {}
};

#endif
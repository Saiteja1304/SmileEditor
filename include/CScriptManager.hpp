#ifndef CSCRIPTMANAGER_HPP
#define CSCRIPTMANAGER_HPP
#include "Editor.hpp"
#include "FileManager.hpp"
#include <Scripting/CScript.hpp>
struct struct_scripts {
    CScript *(*GetPtr)();
    void *handle;
    CScript *script;
};
class CScriptManager {
  public:
    Editor &CSM_editor = CSM_editor.EGetInstance();
    struct_scripts *scripts;
    bool isReCompiled = false;
    FileManager &CSM_filemanager = CSM_filemanager.FMGetInstance();
    static CScriptManager &CSMGetInstance() {
        static CScriptManager CSMInstance;
        return CSMInstance;
    }
    void CSMLoadScripts();
    void CSMReloadScripts();
    void CSMScriptInit();
    void CSMScriptStart();
    void CSMScriptUpdate();
    void CSMScriptExit();
    void CSMDestroyScripts();

  private:
    CScriptManager() {}
    CScriptManager(CScriptManager const &);
    void operator=(CScriptManager const &);
    void __loadScripts();
    void __closehandles();
};

#endif
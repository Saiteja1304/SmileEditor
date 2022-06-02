#ifndef EDITOR_HPP
#define EDITOR_HPP
#include <string>
class Editor {
  public:
    std::string ProjectRootLoc;
    std::string ScriptsLoc;
    std::string SOLoc;
    static Editor &EGetInstance() {
        static Editor EInstance;
        return EInstance;
    }
    void PreInit();
    void Init();
    void PostInit();
    void PreStart();
    void Start();
    void PostStart();
    void Update();
    void preExit();
    void Exit();

  private:
    Editor() {}
    Editor(Editor const &);
    void operator=(Editor const &);
};

#endif
#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP
#include "Editor.hpp"
#include <string>
#include <vector>
class FileManager {
  public:
    Editor *FMEditor = FMEditor->EGetInstance();
    std::vector<std::string> files;
    std::vector<std::string> SharedObjects;
    static FileManager *FMInstance;
    static FileManager *FMGetInstance() {
        if (!FMInstance)
            FMInstance = new FileManager;
        return FMInstance;
    }
    void SearchSharedObjects();

  private:
  void __DeleteDuplicates();
    FileManager() {}
    ~FileManager() {}
};

#endif
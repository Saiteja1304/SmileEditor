#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP
#include "Editor.hpp"
#include <string>
#include <vector>
class FileManager {
  public:
    Editor &FMEditor = FMEditor.EGetInstance();
    std::vector<std::string> files;
    std::vector<std::string> SharedObjects;
    static FileManager &FMGetInstance() {
        static FileManager FMInstance;
        return FMInstance;
    }
    void SearchSharedObjects();

  private:
    void __DeleteDuplicates();
    FileManager() {}
    FileManager(FileManager const &);
    void operator=(FileManager const &);
};

#endif
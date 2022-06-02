#include <FileManager.hpp>
#include <dirent.h>
#include <iostream>
#include <string.h>
DIR *dr;
struct dirent *entity;

void FileManager::__DeleteDuplicates() {
    if (SharedObjects.size() > 1) {
        for (int i = SharedObjects.size(); i > 0; i++) {
            if (SharedObjects[i] == SharedObjects[i - 1]) {
                SharedObjects.erase(SharedObjects.begin() + i);
            }
        }
    }
}

void FileManager::SearchSharedObjects() {
    SharedObjects.clear();
    dr = opendir((FMEditor.SOLoc).c_str());
    if (dr) {
        while ((entity = readdir(dr)) != NULL) {
            if ((int)(entity->d_type) == 8) {
                SharedObjects.push_back(entity->d_name);
            }
        }
        closedir(dr);
    }
    __DeleteDuplicates();
}
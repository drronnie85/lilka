#pragma once

#include "app.h"
#include <string>
#include <ctime>
#include <dirent.h>
#include <errno.h>
#define APP_FBROWSER_NAME "FileBrowser"
class FileBrowserApp : public App {
private:
    String getHumanReadableSize(size_t size);
    String getFileInfo(const String& filePath);
    const menu_icon_t* getFileIcon(const String& filename);
    const uint16_t getFileColor(const String& filename);
    void openFile(String path);
    void openPath(const String& path);
    // Fields:
    String currentPath;
    DIR* currentDir;
    // Blocking Draw Functions:
    void alertDraw(const String title, const String message);
    void menuDraw(lilka::Menu& menu);

public:
    // TODO: Refactor this place, probably pass
    void setPath(const String path);
    FileBrowserApp();

    void run() override;
};

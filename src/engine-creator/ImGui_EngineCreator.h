#pragma once

#include "imgui.h"
#include <misc/cpp/imgui_stdlib.h>
#include "EngineCreator.h"

class ImGui_EngineCreator
{
public:
    ImGui_EngineCreator();
    void editText(const std::string& name);
    void editFloat(const std::string& name);
    void editInt(const std::string& name);
    void showSaveButton();
    void showEditedEngineFile();
    void showSaveAsWindow();
    void showInputValues();
    void setScroll(const unsigned int lineNumber);

private:
    EngineCreator engineCreator;
    bool show_save_as_window;
    char newFileName[128] = "NewFileName";
    bool scrollToLine;
    unsigned int lineToScroll;
    static inline Unit::Units unitTypes;
};
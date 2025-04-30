#include <iostream>

#include "EngineCreator.h"

int main(int argc, char **argv)
{
    std::cout << "\n\nEngine Creator v0.01\n";
    EngineCreator engineCreator;
    engineCreator.setCreatedEngineFileName("created_engine_2");
    std::string newName = "CreatedEngine2";
    std::string newLine = "        name: \"" + newName + "\",";
    engineCreator.changeLineTo(134, newLine);
    engineCreator.writeAllLinesToFile();
}
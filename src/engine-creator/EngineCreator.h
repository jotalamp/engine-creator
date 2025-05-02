#pragma once

#include <iostream>
#include <bits/stdc++.h>

class EngineCreator
{
public:
    EngineCreator();
    std::string getOriginalLine(unsigned int lineNumber);
    std::string getEditedLine(unsigned int lineNumber);
    std::string getLineFromCreatedFile(unsigned int lineNumber);
    void changeLineTo(unsigned int lineNumber, std::string newLineText);
    void writeAllLinesToFile();
    bool setCreatedEngineFileName(std::string newFileName);
    std::string getAllEditedLinesAsString();
    bool fileNameIsCorrect(std::string newFileName);
    bool textExistsInOriginalLine(unsigned int lineNumber, std::string textToFind);
    bool textExistsInEditedLine(unsigned int lineNumber, std::string textToFind);
    void replaceTextInLine(unsigned int lineNumber, std::string textToReplace, std::string newText);
    char* getChangeableTextInLine(unsigned int lineNumber);
private:
    std::vector<std::string> originalLines;
    std::vector<std::string> editedLines;
    char* changeableText[500];
    void setChangeAbleTextInLine(unsigned int lineNumber, char changeableText[128]);
    std::string getLineFromFile(std::string fileName, unsigned int lineNumber);
    static const inline std::string path = "../bin/";
    static const inline std::string exampleEngineName = "example_engine.mr";
    static inline std::string createdEngineName = "created_engine.mr";
};
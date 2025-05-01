#pragma once

#include <iostream>
#include <bits/stdc++.h>

class EngineCreator
{
public:
    EngineCreator();
    std::string getLine(unsigned int lineNumber);
    std::string getLineFromCreatedFile(unsigned int lineNumber);
    void changeLineTo(unsigned int lineNumber, std::string newLineText);
    void writeAllLinesToFile();
    void setCreatedEngineFileName(std::string newFileName);
    std::string getAllLinesAsString();
private:
    std::vector<std::string> lines;
    std::string getLineFromFile(std::string fileName, unsigned int lineNumber);
    static const inline std::string path = "../bin/";
    static const inline std::string exampleEngineName = "example_engine.mr";
    static inline std::string createdEngineName = "created_engine.mr";
};
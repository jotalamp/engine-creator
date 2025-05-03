#pragma once

#include <iostream>
#include <bits/stdc++.h>

enum class ValueType
{
    Text, 
    Int,
    Decimal
};

class EditableLine
{
public:
    EditableLine(unsigned int lineNumber, std::string name, std::string editableText, ValueType type=ValueType::Text);
    bool operator==(const EditableLine &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name;
    }
    std::string getName() const;
    std::string getEditableText() const;
    std::string* getEditedText();
    unsigned int getLineNumber() const;
    ValueType getValueType() const;
private:
    unsigned int lineNumber;
    std::string name;
    std::string editableText;
    std::string originalLineText;
    std::string editedLineText;
    std::string editedText;
    ValueType valueType = ValueType::Text;
};

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
    void addEditableLine(const EditableLine& editableLine);
    EditableLine* getEditableLine(unsigned int lineNumber);
private:
    std::vector<std::string> originalLines;
    std::vector<std::string> editedLines;
    std::unordered_map<unsigned int, EditableLine> editableLines;
    std::string getLineFromFile(std::string fileName, unsigned int lineNumber);
    static const inline std::string path = "../bin/";
    static const inline std::string exampleEngineName = "example_engine.mr";
    static inline std::string createdEngineName = "created_engine.mr";
};
#pragma once

#include <iostream>
#include <bits/stdc++.h>
#include <iomanip>
#include <sstream>

class TextNotFoundFromTemplateFileException : public std::exception
{
private:
    std::string message;

public:
    TextNotFoundFromTemplateFileException(std::string msg)
        : message(msg)
    {
    }

    const char *what() const throw()
    {
        return message.c_str();
    }
};

class EditableLineNotExistException : std::exception
{
};
class FileNotFoundException : std::exception
{
};

class TextCanNotBeConvertedToNumberException : public std::exception
{
private:
    std::string message;

public:
    // Constructor accepts a const char* that is used to set
    // the exception message
    TextCanNotBeConvertedToNumberException(const char *msg)
        : message(msg)
    {
    }

    // Override the what() method to return our message
    const char *what() const throw()
    {
        return message.c_str();
    }
};

class EditableLine
{
public:
    EditableLine(unsigned int lineNumber, std::string name, std::string editableText);
    bool operator==(const EditableLine &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name;
    }
    std::string getName() const;
    std::string getEditableText() const;
    std::string *getEditedText();
    unsigned int getLineNumber() const;

protected:
    unsigned int lineNumber;
    std::string name;
    std::string editableText;
    std::string editedText;
};

class EditableFloatValue : public EditableLine
{
public:
    EditableFloatValue(unsigned int lineNumber, std::string name, std::string editableText, float defaultValue);
    EditableFloatValue(unsigned int lineNumber, std::string name, std::string editableText);
    bool operator==(const EditableFloatValue &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name;
    }
    float *getEditedFloatValue();
    std::string getEditedValueAsString();

private:
    float editedFloatValue;
};

class EditableIntegerValue : public EditableLine
{
public:
    EditableIntegerValue(unsigned int lineNumber, std::string name, std::string editableText, int defaultValue);
    EditableIntegerValue(unsigned int lineNumber, std::string name, std::string editableText);
    bool operator==(const EditableIntegerValue &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name;
    }
    int *getEditedIntegerValue();
    std::string getEditedValueAsString();

private:
    int editedIntValue;
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
    void addEditableLine(const EditableLine &editableLine);
    void addEditableFloatValue(const EditableFloatValue &editableFloatValue);
    void addEditableIntegerValue(const EditableIntegerValue &editableIntegerValue);
    EditableLine *getEditableLine(unsigned int lineNumber);
    EditableFloatValue *getEditableFloatValue(unsigned int lineNumber);
    EditableIntegerValue *getEditableIntegerValue(unsigned int lineNumber);

private:
    std::vector<std::string> originalLines;
    std::vector<std::string> editedLines;
    std::unordered_map<unsigned int, EditableLine> editableLines;
    std::unordered_map<unsigned int, EditableFloatValue> editableFloatValues;
    std::unordered_map<unsigned int, EditableIntegerValue> editableIntegerValues;
    std::string getLineFromFile(std::string fileName, unsigned int lineNumber);
    static const inline std::string path = "../bin/";
    static const inline std::string templateEngineName = "template_engine.mr";
    static inline std::string createdEngineName = "created_engine.mr";
};
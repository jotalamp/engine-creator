#pragma once

#include <iostream>
#include <bits/stdc++.h>
#include <iomanip>
#include <sstream>
#include <assert.h>

class EngineCreatorException : public std::exception
{
public:
    EngineCreatorException(std::string message)
    {
        this->message = message;
    }

    const char *what() const throw()
    {
        return message.c_str();
    }

protected:
    std::string message;
};

class TextNotFoundFromTemplateFileException : public EngineCreatorException
{
public:
    TextNotFoundFromTemplateFileException(std::string message) : EngineCreatorException(message) {}
};

class EditableLineNotExistException : EngineCreatorException
{
public:
    EditableLineNotExistException(unsigned int lineNumber) : EngineCreatorException("Editable line not exist at line: " 
        + std::to_string(lineNumber)) 
    {
    }

    EditableLineNotExistException(std::string name) : EngineCreatorException("Editable line not exist: " + name) 
    {
    }

    const char *what() const throw()
    {
        return message.c_str();
    }
};

class FileNotFoundException : public EngineCreatorException
{
public:
    FileNotFoundException(std::string message) : EngineCreatorException(message) {}
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
    std::string getEditedValueAsString(unsigned char decimals);

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
    void addEditableLine(unsigned int lineNumber, std::string name, std::string editableText);
    void addEditableFloatValue(unsigned int lineNumber, std::string name, std::string editableText);
    void addEditableIntegerValue(unsigned int lineNumber, std::string name, std::string editableText);
    EditableLine *getEditableLine(unsigned int lineNumber);
    EditableLine *getEditableLine(std::string name);
    EditableFloatValue *getEditableFloatValue(unsigned int lineNumber);
    EditableFloatValue *getEditableFloatValue(std::string name);
    EditableIntegerValue *getEditableIntegerValue(unsigned int lineNumber);
    EditableIntegerValue *getEditableIntegerValue(std::string name);

    std::unordered_map<std::string, EditableLine> getEditableTextValuesByName() const;
    std::unordered_map<std::string, EditableFloatValue> getEditableFloatValuesByName() const;
    std::unordered_map<std::string, EditableIntegerValue> getEditableIntegerValuesByName() const;

private:
    void addEditableLine(const EditableLine &editableLine);
    void addEditableFloatValue(const EditableFloatValue &editableFloatValue);
    void addEditableIntegerValue(const EditableIntegerValue &editableIntegerValue);
    std::vector<std::string> originalLines;
    std::vector<std::string> editedLines;
    std::unordered_map<unsigned int, EditableLine> editableLines;
    std::unordered_map<unsigned int, EditableFloatValue> editableFloatValues;
    std::unordered_map<unsigned int, EditableIntegerValue> editableIntegerValues;
    std::unordered_map<std::string, EditableLine> editableTextValuesByName;
    std::unordered_map<std::string, EditableFloatValue> editableFloatValuesByName;
    std::unordered_map<std::string, EditableIntegerValue> editableIntegerValuesByName;
    std::string getLineFromFile(std::string fileName, unsigned int lineNumber);
    static const inline std::string path = "../bin/";
    static const inline std::string templateEngineName = "template_engine.mr";
    static inline std::string createdEngineName = "created_engine.mr";
};
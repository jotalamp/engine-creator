#pragma once

#include <charconv>

#include "EditableValue.h"

class EngineCreatorException : public std::exception
{
public:
    EngineCreatorException(const std::string& message)
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
    TextNotFoundFromTemplateFileException(const std::string& message) : EngineCreatorException(message) {}
};

class EditableStringValueNotExistException : public EngineCreatorException
{
public:
    EditableStringValueNotExistException(unsigned int lineNumber) : EngineCreatorException("Editable line not exist at line: " + std::to_string(lineNumber))
    {
    }

    EditableStringValueNotExistException(const std::string& name) : EngineCreatorException("Editable line not exist: " + name)
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
    FileNotFoundException(const std::string& message) : EngineCreatorException(message) {}
};

class EngineCreator
{
public:
    EngineCreator();
    EditableStringValue *getEditableStringValue(std::string name);
    EditableFloatValue *getEditableFloatValue(std::string name);
    EditableIntegerValue *getEditableIntegerValue(std::string name);
    void replaceTextInLine(unsigned int lineNumber, std::string textToReplace, std::string newText);
    std::string replaceEditedTextInLine(unsigned int lineNumber, std::string textToReplace, std::string newText);
    std::string replaceTextInText(std::string& text, const std::string& textToReplace, const std::string& newText);
    void writeAllLinesToFile() const;
    std::string getAllEditedLinesAsString() const;
    bool fileNameIsCorrect(std::string newFileName) const;
    bool setCreatedEngineFileName(std::string newFileName);

    EditableStringValue addEditableValue(unsigned int lineNumber, std::string name, std::string editableValue);
    EditableFloatValue addEditableValue(unsigned int lineNumber, std::string name, double editableValue);
    EditableIntegerValue addEditableValue(unsigned int lineNumber, std::string name, int editableValue);

    unsigned int getLineCount() const;
    std::string getEditedLine(unsigned int lineNumber) const;
    std::string shortestStringRepresentation(float n) const;
    //std::string setUnitType(EditableNumericValue& editableNumericValue, const UnitType& unitType, std::string text);

private:
    std::string getOriginalLine(unsigned int lineNumber) const;
    std::string getLineFromCreatedFile(unsigned int lineNumber) const;
    void changeLineTo(unsigned int lineNumber, std::string newLineText);
    bool textExistsInOriginalLine(unsigned int lineNumber, std::string textToFind) const;
    bool textExistsInEditedLine(unsigned int lineNumber, std::string textToFind) const;

    EditableStringValue addEditableStringValue(unsigned int lineNumber, std::string name, std::string editableText);
    EditableFloatValue addEditableFloatValue(unsigned int lineNumber, std::string name, std::string editableText);
    EditableIntegerValue addEditableIntegerValue(unsigned int lineNumber, std::string name, std::string editableText);

    std::unordered_map<std::string, EditableStringValue> getEditableTextValuesByName() const;
    std::unordered_map<std::string, EditableFloatValue> getEditableFloatValuesByName() const;
    std::unordered_map<std::string, EditableIntegerValue> getEditableIntegerValuesByName() const;

    EditableStringValue *getEditableStringValue(unsigned int lineNumber);

    EditableStringValue addEditableStringValue(const EditableStringValue &EditableStringValue);
    EditableFloatValue addEditableFloatValue(EditableFloatValue &editableFloatValue);
    EditableIntegerValue addEditableIntegerValue(EditableIntegerValue &editableIntegerValue);

    std::vector<std::string> originalLines;
    std::vector<std::string> editedLines;
    std::unordered_map<std::string, EditableStringValue> editableTextValuesByName;
    std::unordered_map<std::string, EditableFloatValue> editableFloatValuesByName;
    std::unordered_map<std::string, EditableIntegerValue> editableIntegerValuesByName;
    std::string getLineFromFile(std::string fileName, unsigned int lineNumber) const;
    static const inline std::string path = "../bin/";
    static const inline std::string templateEngineName = "template_engine.mr";
    static inline std::string createdEngineName = "created_engine.mr";
    unsigned int linesCount = 0;
};

#pragma once

#include <charconv>

#include "Units.h"
#include "EditableValue.h"

class EngineCreatorException : public std::exception
{
public:
    EngineCreatorException(const std::string &message)
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

class EditableValueNotExistException : public EngineCreatorException
{
public:
    EditableValueNotExistException(unsigned int lineNumber) : EngineCreatorException("Editable line not exist at line: " + std::to_string(lineNumber))
    {
    }

    EditableValueNotExistException(const std::string &name) : EngineCreatorException("Editable value not exist: '" + name + "'")
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
    FileNotFoundException(const std::string &message) : EngineCreatorException(message) {}
};

class EngineCreator
{
public:
    EngineCreator();

    EditableStringValue *getEditableStringValue(const std::string &name);
    EditableFloatValue *getEditableFloatValue(const std::string &name);
    EditableIntegerValue *getEditableIntegerValue(const std::string &name);

    void writeAllLinesToFile() const;
    std::string getAllEditedLinesAsString() const;
    bool fileNameIsCorrect(const std::string &newFileName) const;
    bool setCreatedEngineFileName(const std::string &newFileName);

    void addEditableValue(unsigned int lineNumber, const std::string &name, const std::string &editableValue);
    void addEditableValue(unsigned int lineNumber, const std::string &name, double editableValue, unsigned int decimals = 3);
    void addEditableValue(unsigned int lineNumber, const std::string &name, int editableValue);

    unsigned int getLineCount() const;
    std::string shortestStringRepresentation(float n) const;

private:
    auto getEditableTextValuesByName() const;
    auto getEditableFloatValuesByName() const;
    auto getEditableIntegerValuesByName() const;

    void addEditableValue(const EditableStringValue &EditableStringValue);
    void addEditableValue(const EditableFloatValue &editableFloatValue);
    void addEditableValue(const EditableIntegerValue &editableIntegerValue);

    std::unordered_map<std::string, EditableStringValue> editableTextValuesByName;
    std::unordered_map<std::string, EditableFloatValue> editableFloatValuesByName;
    std::unordered_map<std::string, EditableIntegerValue> editableIntegerValuesByName;

    std::vector<std::string> editedLines;
    static const inline std::string path = "./bin/";
    static const inline std::string templateEngineName = "template_engine.mr";
    static inline std::string createdEngineName = "created_engine.mr";
    unsigned int linesCount = 0;
};

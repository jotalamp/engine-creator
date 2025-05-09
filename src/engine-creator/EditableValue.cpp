#include "EditableValue.h"

EditableValue::EditableValue(unsigned int lineNumber, const std::string &name, const std::string &editableText)
{
    this->lineNumber = lineNumber;
    this->name = name;
    this->editableText = editableText;
}

std::string EditableValue::getName() const
{
    return name;
}

std::string EditableValue::getEditableText() const
{
    return editableText;
}

unsigned int EditableValue::getLineNumber() const
{
    return lineNumber;
}

EditableStringValue::EditableStringValue(unsigned int lineNumber, const std::string &name, const std::string &editableText)
    : EditableValue(lineNumber, name, editableText)
{
    this->editedText = editableText;
}

std::string *EditableStringValue::getEditedText()
{
    return &editedText;
}

EditableFloatValue::EditableFloatValue(unsigned int lineNumber, const std::string &name, const std::string &editableText)
    : EditableValue(lineNumber, name, editableText)
{
    try
    {
        float defaultValue = std::stof(editableText);
        editedFloatValue = defaultValue;
    }
    catch (const std::exception &e)
    {
        throw CanNotConvertStringToFloatException(editableText);
    }
}

float *EditableFloatValue::getEditedFloatValue()
{
    return &editedFloatValue;
}

std::string EditableFloatValue::getEditedValueAsString(unsigned char decimals)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(decimals) << editedFloatValue;
    return stream.str();
}

EditableIntegerValue::EditableIntegerValue(unsigned int lineNumber, const std::string &name, const std::string &editableText) 
    : EditableValue(lineNumber, name, editableText)
{
    try
    {
        int defaultValue = std::stof(editableText);
        editedIntValue = defaultValue;
    }
    catch (const std::exception &e)
    {
        throw CanNotConvertStringToIntException(editableText);
    }
}

int *EditableIntegerValue::getEditedIntegerValue()
{
    return &editedIntValue;
}

std::string EditableIntegerValue::getEditedValueAsString()
{
    return std::to_string(editedIntValue);
}
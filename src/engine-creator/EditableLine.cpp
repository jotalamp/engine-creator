#include "EditableLine.h"

EditableLine::EditableLine(unsigned int lineNumber, const std::string& name, const std::string& editableText)
{
    this->lineNumber = lineNumber;
    this->name = name;
    this->editableText = editableText;
    this->editedText = editableText;
}

std::string EditableLine::getName() const
{
    return name;
}

std::string EditableLine::getEditableText() const
{
    return editableText;
}

std::string *EditableLine::getEditedText()
{
    return &editedText;
}

unsigned int EditableLine::getLineNumber() const
{
    return lineNumber;
}

EditableFloatValue::EditableFloatValue(unsigned int lineNumber, const std::string& name, const std::string& editableText, float defaultValue) : EditableLine(lineNumber, name, editableText)
{
    editedFloatValue = defaultValue;
}

EditableFloatValue::EditableFloatValue(unsigned int lineNumber, const std::string& name, const std::string& editableText) : EditableFloatValue(lineNumber, name, editableText, std::stof(editableText))
{
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

EditableIntegerValue::EditableIntegerValue(unsigned int lineNumber, const std::string& name, const std::string& editableText, int defaultValue) : EditableLine(lineNumber, name, editableText)
{
    editedIntValue = defaultValue;
}

EditableIntegerValue::EditableIntegerValue(unsigned int lineNumber, const std::string& name, const std::string& editableText) : EditableIntegerValue(lineNumber, name, editableText, std::stof(editableText))
{
}

int *EditableIntegerValue::getEditedIntegerValue()
{
    return &editedIntValue;
}

std::string EditableIntegerValue::getEditedValueAsString()
{
    return std::to_string(editedIntValue);
}
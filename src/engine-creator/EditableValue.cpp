#include "EditableValue.h"

EditableValue::EditableValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *lineText)
{
    this->originalLine = lineText;
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

std::string EditableValue::getLineText() const
{
    return *originalLine;
}

void EditableValue::setLineText(const std::string &newLineText)
{
    *originalLine = newLineText;
}

unsigned int EditableValue::getLineNumber() const
{
    return lineNumber;
}

EditableNumericValue::EditableNumericValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *lineText)
    : EditableValue(lineNumber, name, editableText, lineText)
{
}

UnitType EditableNumericValue::getUnitType() const
{
    return unitType;
}

UnitType EditableNumericValue::getUnitType(const std::string &unitTypeAsString) const
{
    return unitTypes2[unitTypeAsString];
}

std::string EditableNumericValue::getUnitTypeAsString() const
{
    return unitTypes[this->unitType];
}

std::string EditableNumericValue::getUnitTypeAsString(const UnitType &unitType) const
{
    return unitTypes[unitType];
}

inline const std::unordered_map<UnitType, std::string> &EditableNumericValue::getUnitTypes()
{
    return unitTypes;
}

void EditableNumericValue::setUnitType()
{
    if (originalLine == nullptr)
        throw LineTextNotExistException(name);

    std::string line = *originalLine;

    for (auto anUnitType : unitTypes)
    {
        auto it = unitTypes.find(anUnitType.first);
        std::string textToReplace = it->second;

        auto &&pos = line.find(textToReplace, size_t{});
        if (pos != std::string::npos)
        {
            this->unitType = anUnitType.first;
        }
    }
}

void EditableNumericValue::setUnitType(const UnitType &unitType)
{
    if (originalLine == nullptr)
        throw LineTextNotExistException(name);

    std::string line = *originalLine;

    std::string textToReplace = unitTypes[this->unitType];

    auto &&pos = line.find(textToReplace, size_t{});
    if (pos != std::string::npos)
    {
        this->unitType = unitType;
    }
    this->unitType = unitType;
}

EditableStringValue::EditableStringValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *lineText)
    : EditableValue(lineNumber, name, editableText, lineText)
{
    this->editedText = editableText;
}

std::string *EditableStringValue::getEditedText()
{
    return &editedText;
}

EditableFloatValue::EditableFloatValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *lineText)
    : EditableNumericValue(lineNumber, name, editableText, lineText)
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

EditableIntegerValue::EditableIntegerValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *lineText)
    : EditableNumericValue(lineNumber, name, editableText, lineText)
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

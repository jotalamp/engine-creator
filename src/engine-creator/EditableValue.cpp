#include "EditableValue.h"

Units::Unit unitTypes;

EditableValue::EditableValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *editedLine)
{
    if (editedLine == nullptr)
        throw EditedLineIsNullPointerException(name);

    this->originalLine = *editedLine;
    this->lineNumber = lineNumber;
    this->name = name;
    this->editableText = editableText;
    this->editedLine = editedLine;
    this->editedValue = editableText;

    calculateStartTextEndLetterPosition();
    calculateEndTextStartLetterPosition();
}

std::string EditableValue::getName() const
{
    return name;
}

std::string EditableValue::getEditableText() const
{
    return editableText;
}

std::string* EditableValue::getEditedValue()
{
    return &editedValue;
}

std::string EditableValue::getOriginalLine() const
{
    return originalLine;
}

std::string& EditableValue::getEditedLine() const
{
    if (editedLine == nullptr)
        throw EditedLineIsNullPointerException(name);

    return *editedLine;
}

void EditableValue::calculateEndTextStartLetterPosition()
{
    endTextStartLetterPosition = startTextEndLetterPosition + editableText.length();
}

unsigned int EditableValue::getStartTextEndLetterPosition() const
{
    return startTextEndLetterPosition;
}

unsigned int EditableValue::getEndTextStartLetterPosition() const
{
    return endTextStartLetterPosition;
}

std::string EditableValue::getTextStart() const
{
    return getOriginalLine().substr(0, getStartTextEndLetterPosition());
}

unsigned int EditableValue::getLineNumber() const
{
    return lineNumber;
}

EditableNumericValue::EditableNumericValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *editedLine)
    : EditableValue(lineNumber, name, editableText, editedLine)
{
    setUnitType();
    originalUnitType = this->unitType;
    calculateEndTextStartLetterPosition();
}

std::string EditableNumericValue::getTextEnd() const
{
    int p = getEndTextStartLetterPosition();
    int l = getOriginalLine().length();
    if (p > l)
        throw TextNotFoundException(std::to_string(p) + ":" + std::to_string(l));
    return getOriginalLine().substr(getEndTextStartLetterPosition());
}

std::string EditableNumericValue::getTextMiddle() const
{
    return " * ";
    // return getOriginalLine().substr(getEditableTextStartLetterPosition() + editableText.length(), getUnitEndLetterPosition() - 1-unitTypes[unitType].length());
}

UnitType EditableNumericValue::getUnitType() const
{
    return unitType;
}

std::string EditableNumericValue::getUnitTypeAsString() const
{
    return Units::Unit{}[this->unitType];
}

void EditableNumericValue::setUnitType()
{
    std::string line = originalLine;

    for (auto anUnitType : Units::Unit{}.getUnitToStringMap())
    {
        auto it = Units::Unit{}.getUnitToStringMap().find(anUnitType.first);
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
    this->unitType = unitType;

    if (unitType == UnitType::None)
    {
        *editedLine = getTextStart() + editedValue + getTextEnd();
    }
    else
    {
        *editedLine = getTextStart() + editedValue + getTextMiddle() + unitTypes[unitType] + getTextEnd();
    }
}

void EditableNumericValue::calculateEndTextStartLetterPosition()
{
    if (unitType == UnitType::None)
    {
        endTextStartLetterPosition = startTextEndLetterPosition + editableText.length();
    }
    else
    {
        auto &&pos = getOriginalLine().find(unitTypes[originalUnitType], size_t{});
        if (pos != std::string::npos)
        {
            endTextStartLetterPosition = pos + unitTypes[originalUnitType].length();
        }
        else
            throw TextNotFoundException(unitTypes[originalUnitType] + " : " + getOriginalLine());
    }
}

void EditableValue::calculateStartTextEndLetterPosition()
{
    auto &&pos = getOriginalLine().find(editableText, size_t{});
    if (pos != std::string::npos)
    {
        startTextEndLetterPosition = pos;
    }
    else
        throw TextNotFoundException(editableText + " : " + getOriginalLine());
}

std::string EditableValue::replaceTextInText(const std::string &text, const std::string &textToReplace, const std::string &newText)
{
    std::string line = text;

    auto &&pos = line.find(textToReplace, size_t{});
    if (pos != std::string::npos)
    {
        line.replace(pos, textToReplace.length(), newText);
        pos = textToReplace.find(textToReplace, pos + newText.length());
    }
    return line;
}

EditableStringValue::EditableStringValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *editedLine)
    : EditableValue(lineNumber, name, editableText, editedLine)
{
    this->editableText = editableText;
    this->editedValue = editableText;
}

std::string EditableStringValue::getTextEnd() const
{
    int p = getEndTextStartLetterPosition();
    int l = getOriginalLine().length();
    if (p > l)
        throw TextNotFoundException(std::to_string(p) + ":" + std::to_string(l));
    return getOriginalLine().substr(getEndTextStartLetterPosition());
}

void EditableStringValue::setValue(const std::string& newValue)
{
    //if (editedLine == nullptr)
      //  throw EditedLineIsNullPointerException(name);

    editedValue = newValue;

    *editedLine = getTextStart() + editedValue + getTextEnd();
}

std::string &EditableStringValue::getEditedLine()
{
    return *editedLine;
}

EditableFloatValue::EditableFloatValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *editedLine)
    : EditableNumericValue(lineNumber, name, editableText, editedLine)
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

void EditableFloatValue::setValue(const float newValue)
{
    //if (editedLine == nullptr)
       // throw EditedLineIsNullPointerException(name);

    editedFloatValue = newValue;

    // editedValue = shortestStringRepresentation(newValue);
    editedValue = getEditedValueAsString(3);

    if (unitType == UnitType::None)
    {
        *editedLine = getTextStart() + editedValue + getTextEnd();
    }
    else
    {
        *editedLine = getTextStart() + editedValue + getTextMiddle() + unitTypes[unitType] + getTextEnd();
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

std::string EditableFloatValue::shortestStringRepresentation(float n) const
{
    if (n == 1.0f)
        return "1.0"; // special case to get smaller increment steps

    // https://www.reddit.com/user/isfooTM/
    // https://www.reddit.com/r/AskProgramming/comments/swmb96/converting_a_float_to_the_shortest_uniquely/
    std::array<char, 64> buf;
    auto result = std::to_chars(buf.data(), buf.data() + buf.size(), n, std::chars_format::fixed);
    return std::string(buf.data(), result.ptr - buf.data());
}

EditableIntegerValue::EditableIntegerValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *editedLine)
    : EditableNumericValue(lineNumber, name, editableText, editedLine)
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

void EditableIntegerValue::setValue(const int newValue)
{
    //if (editedLine == nullptr)
       // throw EditedLineIsNullPointerException(name);

    editedIntValue = newValue;

    editedValue = std::to_string(newValue);

    if (unitType == UnitType::None)
    {
        *editedLine = getTextStart() + editedValue + getTextEnd();
    }
    else
    {
        *editedLine = getTextStart() + editedValue + getTextMiddle() + unitTypes[unitType] + getTextEnd();
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

#include "EditableValue.h"

EditableValue::EditableValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *lineText, std::string *editedText)
{
    this->originalLine = lineText;
    this->lineNumber = lineNumber;
    this->name = name;
    this->editableText = editableText;
    this->editedText = editedText;
}

std::string EditableValue::getName() const
{
    return name;
}

std::string EditableValue::getEditableText() const
{
    return editableText;
}

std::string EditableValue::getOriginalText() const
{
    if(originalLine==nullptr) throw OriginalTextIsNullPointerException(name);

    return *originalLine;
}

std::string EditableValue::getEditedText() const
{
    if(editedText==nullptr) throw EditedTextIsNullPointerException(name);

    return *editedText;
}

void EditableValue::setLineText(const std::string &newLineText)
{
    if(editedText==nullptr) throw EditedTextIsNullPointerException(name);

    *editedText = newLineText;
}

unsigned int EditableValue::getLineNumber() const
{
    return lineNumber;
}

EditableNumericValue::EditableNumericValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *lineText, std::string *editedText)
    : EditableValue(lineNumber, name, editableText, lineText, editedText)
{
    if(lineText) setUnitType();
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
    if (originalLine == nullptr) throw OriginalTextIsNullPointerException(name);

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
        throw OriginalTextIsNullPointerException(name);

    setUnitType();

    std::string line = getEditedText();

    std::string textToReplace = unitTypes[this->unitType];

    auto &&pos = line.find(textToReplace, size_t{});
    if (pos != std::string::npos)
    {
        line.replace(pos, textToReplace.length(), unitTypes[unitType]);
        //this->unitType = unitType;
    }
    *editedText = line;
    this->unitType = unitType;
}

std::string EditableValue::replaceTextInText(const std::string& text, const std::string& textToReplace, const std::string& newText)
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

EditableStringValue::EditableStringValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *lineText, std::string *editedText)
    : EditableValue(lineNumber, name, editableText, lineText, editedText)
{
    this->editedText = editableText;
}

std::string *EditableStringValue::getEditedText()
{
    return &editedText;
}

EditableFloatValue::EditableFloatValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *lineText, std::string *editedText)
    : EditableNumericValue(lineNumber, name, editableText, lineText, editedText)
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
    editedFloatValue = newValue;
    if (editedText == nullptr)
        throw EditedTextIsNullPointerException(name);
    std::cout << "\n" << editableText;
    *editedText = replaceTextInText(getOriginalText(), editableText, shortestStringRepresentation(editedFloatValue));
    editableText = shortestStringRepresentation(editedFloatValue);

    setUnitType(unitType);
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

EditableIntegerValue::EditableIntegerValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *lineText, std::string *editedText)
    : EditableNumericValue(lineNumber, name, editableText, lineText, editedText)
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

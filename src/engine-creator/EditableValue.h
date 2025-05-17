#pragma once

#include <bits/stdc++.h>
#include <string_view>
#include "Units.h"

using Units::UnitType;

class EditableValueException : public std::exception
{
public:
    EditableValueException(const std::string &message)
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

class CanNotConvertStringToFloatException : public EditableValueException
{
public:
    CanNotConvertStringToFloatException(const std::string &message) : EditableValueException("Can not convert string to float! " + message) {}
};

class CanNotConvertStringToIntException : public EditableValueException
{
public:
    CanNotConvertStringToIntException(const std::string &message) : EditableValueException("Can not convert string to int! " + message) {}
};

class OriginalLineIsNullPointerException : public EditableValueException
{
public:
    OriginalLineIsNullPointerException(const std::string &message) : EditableValueException("Original text is nullpointer! " + message) {}
};

class EditedLineIsNullPointerException : public EditableValueException
{
public:
    EditedLineIsNullPointerException(const std::string &message) : EditableValueException("Edited text is nullpointer! " + message) {}
};

class TextNotFoundException : public EditableValueException
{
public:
    TextNotFoundException(const std::string &message) : EditableValueException("\n\tText not found: \n\t" + message + "\n") {}
};

class EditableValue
{
public:
    EditableValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *editedLine);
    virtual bool operator==(const EditableValue &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name;
    }
    virtual bool operator!=(const EditableValue &e2) const
    {
        return !(*this == e2);
    }
    virtual unsigned int getLineNumber() const;
    virtual std::string getName() const;
    virtual std::string getEditableText() const;
    virtual std::string *getEditedValue();
    virtual std::string getOriginalLine() const;
    virtual std::string &getEditedLine() const;
    std::string getTextStart() const;
    void updateLine();
    void setValue(const std::string &newValue);

protected:
    void calculateStartTextEndLetterPosition();
    virtual void calculateEndTextStartLetterPosition();
    std::string replaceTextInText(const std::string &text, const std::string &textToReplace, const std::string &newText);
    unsigned int getStartTextEndLetterPosition() const;
    unsigned int getEndTextStartLetterPosition() const;
    std::string getTextEnd() const;
    unsigned int lineNumber;
    std::string name;
    std::string editableText;
    std::string editedValue;
    std::string *editedLine;
    std::string originalLine;
    unsigned int startTextEndLetterPosition = 0;
    unsigned int endTextStartLetterPosition = 0;
};

class EditableStringValue : public EditableValue
{
public:
    EditableStringValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *editedLine);
    std::string &getEditedLine();

protected:
    std::string editableText;
};

class EditableNumericValue : public EditableValue
{
public:
    EditableNumericValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *editedLine);
    void setUnitType(const UnitType &unitType);
    void setUnitType();
    UnitType getUnitType() const;
    std::string getUnitTypeAsString() const;
    std::string getTextEnd() const;
    std::string getTextMiddle() const;

     
    UnitType unitType = UnitType::None;
    UnitType originalUnitType = UnitType::None;

     static const inline char *items[]{"units.none",
                                  "units.deg",
                                  "units.cc",
                                  "units.thou",
                                  "units.lb_ft",
                                  "units.mm",
                                  "units.g",
                                  "units.rpm",
                                  "units.inch",
                                  "units.kg"};

protected:
    void calculateEndTextStartLetterPosition() override;
};

class EditableFloatValue : public EditableNumericValue
{
public:
    EditableFloatValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *editedLine, unsigned int decimals=3);
    bool operator==(const EditableFloatValue &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name && editedFloatValue == e2.editedFloatValue;
    }
    bool operator!=(const EditableFloatValue &e2) const
    {
        return !(*this == e2);
    }
    void updateLine();
    void setValue(const float newValue);
    float *getEditedFloatValue();
    unsigned int getDecimals() const;
    std::string getEditedValueAsString(unsigned char decimals);

private:
    float editedFloatValue;
    unsigned int decimals;
    std::string shortestStringRepresentation(float n) const;
};

class EditableIntegerValue : public EditableNumericValue
{
public:
    EditableIntegerValue(unsigned int lineNumber, const std::string &name, const std::string &editableText, std::string *editedLine);
    bool operator==(const EditableIntegerValue &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name && editedIntValue == e2.editedIntValue;
    }
    bool operator!=(const EditableIntegerValue &e2) const
    {
        return !(*this == e2);
    }
    void updateLine();
    void setValue(const int newValue);
    int *getEditedIntegerValue();
    std::string getEditedValueAsString();

private:
    int editedIntValue;
};
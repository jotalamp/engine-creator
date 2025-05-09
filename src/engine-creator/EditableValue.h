#pragma once

#include <iostream>
#include <bits/stdc++.h>
#include <sstream>

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
    CanNotConvertStringToFloatException(const std::string &message) : EditableValueException(message) {}
};

class CanNotConvertStringToIntException : public EditableValueException
{
public:
    CanNotConvertStringToIntException(const std::string &message) : EditableValueException(message) {}
};

class EditableValue
{
public:
    EditableValue(unsigned int lineNumber, const std::string &name, const std::string &editableText);
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

protected:
    unsigned int lineNumber;
    std::string name;
    std::string editableText;
};

class EditableStringValue : public EditableValue
{
public:
    EditableStringValue(unsigned int lineNumber, const std::string &name, const std::string &editableText);
    std::string *getEditedText();

protected:
    std::string editedText;
};

enum class UnitType
{
    None,
    Rpm,
    Deg,
    Cc,
    Thou,
    Lb_ft,
    mm,
    g,
    Kg,
    Inch
};

class EditableNumericValue : public EditableValue
{
public:
    EditableNumericValue(unsigned int lineNumber, const std::string &name, const std::string &editableText);
    void setUnitType(const std::string &originalLine);
    UnitType getUnitType() const;
    std::string getUnitTypeAsString() const;
    const static inline std::unordered_map<UnitType, std::string> &getUnitTypes();
    static inline std::unordered_map<UnitType, std::string> unitTypes = {
        {UnitType::None, "units.none"},
        {UnitType::Deg, "units.deg"},
        {UnitType::Cc, "units.cc"},
        {UnitType::Thou, "units.thou"},
        {UnitType::Lb_ft, "units.lb_ft"},
        {UnitType::mm, "units.mm"},
        {UnitType::g, "units.g"},
        {UnitType::Rpm, "units.rpm"},
        {UnitType::Inch, "units.inch"},
        {UnitType::Kg, "units.kg"}};
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
    UnitType unitType = UnitType::None;

protected:
};

class EditableFloatValue : public EditableNumericValue
{
public:
    EditableFloatValue(unsigned int lineNumber, const std::string &name, const std::string &editableText);
    bool operator==(const EditableFloatValue &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name && editedFloatValue == e2.editedFloatValue;
    }
    bool operator!=(const EditableFloatValue &e2) const
    {
        return !(*this == e2);
    }
    float *getEditedFloatValue();
    std::string getEditedValueAsString(unsigned char decimals);

private:
    float editedFloatValue;
};

class EditableIntegerValue : public EditableNumericValue
{
public:
    EditableIntegerValue(unsigned int lineNumber, const std::string &name, const std::string &editableText);
    bool operator==(const EditableIntegerValue &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name && editedIntValue == e2.editedIntValue;
    }
    bool operator!=(const EditableIntegerValue &e2) const
    {
        return !(*this == e2);
    }
    int *getEditedIntegerValue();
    std::string getEditedValueAsString();

private:
    int editedIntValue;
};
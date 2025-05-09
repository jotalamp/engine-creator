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

class EditableFloatValue : public EditableValue
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

class EditableIntegerValue : public EditableValue
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
#pragma once

#include <iostream>
#include <bits/stdc++.h>
#include <sstream>

class EditableLine
{
public:
    EditableLine(unsigned int lineNumber, const std::string& name, const std::string& editableText);
    bool operator==(const EditableLine &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name;
    }
    bool operator!=(const EditableLine &e2) const
    {
        return !(*this==e2);
    }
    unsigned int getLineNumber() const;
    std::string getName() const;
    std::string getEditableText() const;
    std::string *getEditedText();

protected:
    unsigned int lineNumber;
    std::string name;
    std::string editableText;
    std::string editedText;
};

class EditableFloatValue : public EditableLine
{
public:
    EditableFloatValue(unsigned int lineNumber, const std::string& name, const std::string& editableText, float defaultValue);
    EditableFloatValue(unsigned int lineNumber, const std::string& name, const std::string& editableText);
    bool operator==(const EditableFloatValue &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name && editedFloatValue == e2.editedFloatValue;
    }
    bool operator!=(const EditableFloatValue &e2) const
    {
        return !(*this==e2);
    }
    float *getEditedFloatValue();
    std::string getEditedValueAsString(unsigned char decimals);

private:
    float editedFloatValue;
};

class EditableIntegerValue : public EditableLine
{
public:
    EditableIntegerValue(unsigned int lineNumber, const std::string& name, const std::string& editableText, int defaultValue);
    EditableIntegerValue(unsigned int lineNumber, const std::string& name, const std::string& editableText);
    bool operator==(const EditableIntegerValue &e2) const
    {
        return lineNumber == e2.lineNumber && editableText == e2.editableText && name == e2.name && editedIntValue == e2.editedIntValue;
    }
    bool operator!=(const EditableIntegerValue &e2) const
    {
        return !(*this==e2);
    }
    int *getEditedIntegerValue();
    std::string getEditedValueAsString();

private:
    int editedIntValue;
};
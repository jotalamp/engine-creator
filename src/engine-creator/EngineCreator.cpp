#include "EngineCreator.h"

EngineCreator::EngineCreator()
{
    std::ifstream file = std::ifstream(path + templateEngineName);

    // Check if the file is successfully opened
    if (!file.is_open())
    {
        throw FileNotFoundException(std::string("\nError opening the file: " + path + templateEngineName + "\n"));
    }

    // String variable to store the read data
    std::string s;

    // Read each line of the file and print it to the
    // standard output stream till the whole file is
    // completely read
    while (getline(file, s))
    {
        originalLines.push_back(s);
        editedLines.push_back(s);
    }

    // Close the file
    file.close();

    addEditableLine(134, "engine.name", "Audi 2.3 inline 5");
    addEditableIntegerValue(135, "starter_torque", "200");
    addEditableIntegerValue(136, "redline", "6000");
    addEditableFloatValue(138, "fuel.max_turbulence_effect", "2.5");
    addEditableFloatValue(139, "fuel.max_burning_efficiency", "0.75");
    addEditableIntegerValue(18, "rev_limit", "7500");
    addEditableFloatValue(140, "hf_gain", "0.01");
}

std::string EngineCreator::getLineFromFile(std::string fileName, unsigned int lineNumber)
{
    std::vector<std::string> lines;
    std::ifstream file = std::ifstream(path + fileName);

    // Check if the file is successfully opened
    if (!file.is_open())
    {
        std::cerr << "Error opening the file!";
    }

    // String variable to store the read data
    std::string s;

    // Read each line of the file and print it to the
    // standard output stream till the whole file is
    // completely read
    while (getline(file, s))
    {
        lines.push_back(s);
    }

    // Close the file
    file.close();
    return lines[lineNumber];
}

std::string EngineCreator::getOriginalLine(unsigned int lineNumber)
{
    return originalLines[lineNumber];
}

std::string EngineCreator::getEditedLine(unsigned int lineNumber)
{
    return editedLines[lineNumber];
}

std::string EngineCreator::getLineFromCreatedFile(unsigned int lineNumber)
{
    return getLineFromFile(createdEngineName, lineNumber);
}

void EngineCreator::changeLineTo(unsigned int lineNumber, std::string newLineText)
{
    editedLines[lineNumber] = newLineText;
}

void EngineCreator::writeAllLinesToFile()
{
    std::ofstream file(path + createdEngineName);

    for (auto line : editedLines)
    {
        file << line << std::endl;
    }

    file.close();
}

bool EngineCreator::setCreatedEngineFileName(std::string newFileName)
{
    if (fileNameIsCorrect(newFileName))
    {
        createdEngineName = newFileName + ".mr";
        return true;
    }
    return false;
}

std::string EngineCreator::getAllEditedLinesAsString()
{
    std::string allLines;
    for (auto line : editedLines)
    {
        allLines += line + "\n";
    }
    return allLines;
}

bool EngineCreator::fileNameIsCorrect(std::string newFileName)
{
    if (newFileName == "")
        return false;
    return true;
}

bool EngineCreator::textExistsInOriginalLine(unsigned int lineNumber, std::string textToFind)
{
    return (originalLines[lineNumber].find(textToFind) != std::string::npos);
}

bool EngineCreator::textExistsInEditedLine(unsigned int lineNumber, std::string textToFind)
{
    return (editedLines[lineNumber].find(textToFind) != std::string::npos);
}

void EngineCreator::replaceTextInLine(unsigned int lineNumber, std::string textToReplace, std::string newText)
{
    std::string line = originalLines[lineNumber];

    auto &&pos = line.find(textToReplace, size_t{});
    if (pos != std::string::npos)
    {
        line.replace(pos, textToReplace.length(), newText);
        pos = textToReplace.find(textToReplace, pos + newText.length());
    }
    editedLines[lineNumber] = line;
}

void EngineCreator::addEditableLine(const EditableLine &editableLine)
{
    if (!textExistsInOriginalLine(editableLine.getLineNumber(), editableLine.getEditableText()))
    {
        throw TextNotFoundFromTemplateFileException("\nText not found in orginal file: Line " + std::to_string(editableLine.getLineNumber()) + " : " + editableLine.getEditableText());
    }
    editableLines.insert(std::make_pair(editableLine.getLineNumber(), editableLine));
    editableTextValuesByName.insert(std::make_pair(editableLine.getName(), editableLine));
}

void EngineCreator::addEditableFloatValue(const EditableFloatValue &editableFloatValue)
{
    if (!textExistsInOriginalLine(editableFloatValue.getLineNumber(), editableFloatValue.getEditableText()))
    {
        throw TextNotFoundFromTemplateFileException("\nText not found in orginal file: Line " 
            + std::to_string(editableFloatValue.getLineNumber()) + " : " + editableFloatValue.getEditableText());
    }
    editableFloatValues.insert(std::make_pair(editableFloatValue.getLineNumber(), editableFloatValue));
    editableFloatValuesByName.insert(std::make_pair(editableFloatValue.getName(), editableFloatValue));
}

void EngineCreator::addEditableIntegerValue(const EditableIntegerValue &editableIntegerValue)
{
    if (!textExistsInOriginalLine(editableIntegerValue.getLineNumber(), editableIntegerValue.getEditableText()))
    {
        throw TextNotFoundFromTemplateFileException("\nText not found in orginal file: Line " 
            + std::to_string(editableIntegerValue.getLineNumber()) + " : " + editableIntegerValue.getEditableText());
    }
    editableIntegerValues.insert(std::make_pair(editableIntegerValue.getLineNumber(), editableIntegerValue));
    editableIntegerValuesByName.insert(std::make_pair(editableIntegerValue.getName(), editableIntegerValue));
}

void EngineCreator::addEditableLine(unsigned int lineNumber, std::string name, std::string editableText)
{
    addEditableLine(EditableLine(lineNumber, name, editableText));
}

void EngineCreator::addEditableFloatValue(unsigned int lineNumber, std::string name, std::string editableText)
{
    addEditableFloatValue(EditableFloatValue(lineNumber, name, editableText));
}

void EngineCreator::addEditableIntegerValue(unsigned int lineNumber, std::string name, std::string editableText)
{
    addEditableIntegerValue(EditableIntegerValue(lineNumber, name, editableText));
}

EditableLine *EngineCreator::getEditableLine(unsigned int lineNumber)
{
    auto it = editableLines.find(lineNumber);
    if (it != editableLines.end())
    {
        return &it->second;
    }
    else
    {
        throw EditableLineNotExistException(lineNumber);
        return nullptr;
    }
}

EditableLine *EngineCreator::getEditableLine(std::string name)
{
    auto it = editableTextValuesByName.find(name);
    if (it != editableTextValuesByName.end())
    {
        return &it->second;
    }
    else
    {
        throw EditableLineNotExistException(name);
        return nullptr;
    }
}

EditableFloatValue *EngineCreator::getEditableFloatValue(unsigned int lineNumber)
{
    auto it = editableFloatValues.find(lineNumber);
    if (it != editableFloatValues.end())
    {
        return &it->second;
    }
    else
    {
        throw EditableLineNotExistException(lineNumber);
        return nullptr;
    }
}

EditableFloatValue *EngineCreator::getEditableFloatValue(std::string name)
{
    try
    {
        auto it = editableFloatValuesByName.find(name);
        if (it == editableFloatValuesByName.end())
            throw EditableLineNotExistException(name);
        return &it->second;
    }
    catch(const EditableLineNotExistException& e)
    {
        std::cout << "Caught an exception: " << e.what() << std::endl;
        exit(1);
    }
}

EditableIntegerValue *EngineCreator::getEditableIntegerValue(unsigned int lineNumber)
{
    try
    {
        auto it = editableIntegerValues.find(lineNumber);
        if (it == editableIntegerValues.end())
            throw EditableLineNotExistException(lineNumber);
        return &it->second;
    }
    catch (EditableLineNotExistException &e)
    {
        std::cout << "Caught an exception: " << e.what() << std::endl;
        exit(1);
    }
}

EditableIntegerValue *EngineCreator::getEditableIntegerValue(std::string name)
{
    try
    {
        auto it = editableIntegerValuesByName.find(name);
        if (it == editableIntegerValuesByName.end())
            throw EditableLineNotExistException(name);
        return &it->second;
    }
    catch (EditableLineNotExistException &e)
    {
        std::cout << "Caught an exception: " << e.what() << std::endl;
        exit(1);
    }
}

std::unordered_map<std::string, EditableLine> EngineCreator::getEditableTextValuesByName() const
{
    return editableTextValuesByName;
}

std::unordered_map<std::string, EditableFloatValue> EngineCreator::getEditableFloatValuesByName() const
{
    return editableFloatValuesByName;
}

std::unordered_map<std::string, EditableIntegerValue> EngineCreator::getEditableIntegerValuesByName() const
{
    return editableIntegerValuesByName;
}

EditableLine::EditableLine(unsigned int lineNumber, std::string name, std::string editableText)
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

EditableFloatValue::EditableFloatValue(unsigned int lineNumber, std::string name, std::string editableText, float defaultValue) : EditableLine(lineNumber, name, editableText)
{
    editedFloatValue = defaultValue;
}

EditableFloatValue::EditableFloatValue(unsigned int lineNumber, std::string name, std::string editableText) : EditableFloatValue(lineNumber, name, editableText, std::stof(editableText))
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

EditableIntegerValue::EditableIntegerValue(unsigned int lineNumber, std::string name, std::string editableText, int defaultValue) : EditableLine(lineNumber, name, editableText)
{
    editedIntValue = defaultValue;
}

EditableIntegerValue::EditableIntegerValue(unsigned int lineNumber, std::string name, std::string editableText) : EditableIntegerValue(lineNumber, name, editableText, std::stof(editableText))
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

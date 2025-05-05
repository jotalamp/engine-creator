#include "EngineCreator.h"

EngineCreator::EngineCreator()
{
    std::ifstream file = std::ifstream(path + templateEngineName);

    // Check if the file is successfully opened
    if (!file.is_open())
    {
        std::cerr << "\nError opening the file: " + path + templateEngineName + "\n";
        throw FileNotFoundException();
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

    addEditableLine(EditableLine(134, "engine.name", "Audi 2.3 inline 5"));
    addEditableFloatValue(EditableFloatValue(135, "starter_torque", "200", 200.0f));
    addEditableLine(EditableLine(136, "redline", "6000"));
    addEditableLine(EditableLine(138, "fuel.max_turbulence_effect", "2.5"));
    addEditableIntegerValue(EditableIntegerValue(18, "rev_limit", "7500", 7500));
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
    editableLines.insert(std::make_pair(editableLine.getLineNumber(), editableLine));
}

void EngineCreator::addEditableFloatValue(const EditableFloatValue &editableFloatValue)
{
    editableFloatValues.insert(std::make_pair(editableFloatValue.getLineNumber(), editableFloatValue));
}

void EngineCreator::addEditableIntegerValue(const EditableIntegerValue &editableIntegerValue)
{
    editableIntegerValues.insert(std::make_pair(editableIntegerValue.getLineNumber(), editableIntegerValue));
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
        throw EditableLineNotExistException();
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
        throw EditableLineNotExistException();
        return nullptr;
    }
}

EditableIntegerValue *EngineCreator::getEditableIntegerValue(unsigned int lineNumber)
{
    auto it = editableIntegerValues.find(lineNumber);
    if (it != editableIntegerValues.end())
    {
        return &it->second;
    }
    else
    {
        throw EditableLineNotExistException();
        return nullptr;
    }
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

float *EditableFloatValue::getEditedFloatValue()
{
    return &editedFloatValue;
}

std::string EditableFloatValue::getEditedValueAsString()
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << editedFloatValue;
    return stream.str();
}

EditableIntegerValue::EditableIntegerValue(unsigned int lineNumber, std::string name, std::string editableText, int defaultValue): EditableLine(lineNumber, name, editableText)
{
    editedIntValue = defaultValue;
}

int *EditableIntegerValue::getEditedIntegerValue()
{
    return &editedIntValue;
}

std::string EditableIntegerValue::getEditedValueAsString()
{
    return std::to_string(editedIntValue);
}

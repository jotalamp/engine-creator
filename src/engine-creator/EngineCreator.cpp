#include <charconv>

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
        linesCount++;
    }

    // Close the file
    file.close();

   
}

std::string EngineCreator::shortestStringRepresentation(float n) {
    if(n==1.0f) return "1.0";
    std::array<char, 64> buf;
    auto result = std::to_chars(buf.data(), buf.data() + buf.size(), n);
    return std::string(buf.data(), result.ptr - buf.data());
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
    editableTextValuesByName.insert(std::make_pair(editableLine.getName(), editableLine));
}

void EngineCreator::addEditableFloatValue(const EditableFloatValue &editableFloatValue)
{
    if (!textExistsInOriginalLine(editableFloatValue.getLineNumber(), editableFloatValue.getEditableText()))
    {
        throw TextNotFoundFromTemplateFileException("\nText not found in orginal file: Line " 
            + std::to_string(editableFloatValue.getLineNumber()) + " : " + editableFloatValue.getEditableText());
    }
    editableFloatValuesByName.insert(std::make_pair(editableFloatValue.getName(), editableFloatValue));
}

void EngineCreator::addEditableIntegerValue(const EditableIntegerValue &editableIntegerValue)
{
    if (!textExistsInOriginalLine(editableIntegerValue.getLineNumber(), editableIntegerValue.getEditableText()))
    {
        throw TextNotFoundFromTemplateFileException("\nText not found in orginal file: Line " 
            + std::to_string(editableIntegerValue.getLineNumber()) + " : " + editableIntegerValue.getEditableText());
    }
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

void EngineCreator::addEditableValue(unsigned int lineNumber, std::string name, std::string editableValue)
{
    addEditableLine(lineNumber, name, editableValue);
}

void EngineCreator::addEditableValue(unsigned int lineNumber, std::string name, double editableValue)
{
    addEditableFloatValue(lineNumber, name, shortestStringRepresentation(editableValue));
}

void EngineCreator::addEditableValue(unsigned int lineNumber, std::string name, int editableValue)
{
    addEditableIntegerValue(lineNumber, name, shortestStringRepresentation(editableValue));
}

unsigned int EngineCreator::getLineCount() const
{
    return linesCount;
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
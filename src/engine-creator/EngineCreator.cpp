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
        // originalLines.push_back(s);
        editedLines.push_back(s);
        linesCount++;
    }

    // Close the file
    file.close();
}

std::string EngineCreator::shortestStringRepresentation(float n) const
{
    if (n == 1.0f)
        return "1.0"; // special case to get smaller increment steps

    // https://www.reddit.com/user/isfooTM/
    // https://www.reddit.com/r/AskProgramming/comments/swmb96/converting_a_float_to_the_shortest_uniquely/
    std::array<char, 64> buf;
    auto result = std::to_chars(buf.data(), buf.data() + buf.size(), n, std::chars_format::fixed);
    return std::string(buf.data(), result.ptr - buf.data());
}

void EngineCreator::writeAllLinesToFile() const
{
    std::ofstream file(path + createdEngineName);

    for (auto line : editedLines)
    {
        file << line << std::endl;
    }

    file.close();
}

std::string EngineCreator::getAllEditedLinesAsString() const
{
    std::string allLines;
    for (auto line : editedLines)
    {
        allLines += line + "\n";
    }
    return allLines;
}

bool EngineCreator::fileNameIsCorrect(const std::string &newFileName) const
{
    if (newFileName == "")
        return false;
    return true;
}

bool EngineCreator::setCreatedEngineFileName(const std::string &newFileName)
{
    if (fileNameIsCorrect(newFileName))
    {
        createdEngineName = newFileName + ".mr";
        return true;
    }
    return false;
}

void EngineCreator::addEditableValue(const EditableStringValue &editableStringValue)
{
    editableTextValuesByName.insert(std::make_pair(editableStringValue.getName(), editableStringValue));
}

void EngineCreator::addEditableValue(const EditableFloatValue &editableFloatValue)
{
    editableFloatValuesByName.insert(std::make_pair(editableFloatValue.getName(), editableFloatValue));
}

void EngineCreator::addEditableValue(const EditableIntegerValue &editableIntegerValue)
{
    editableIntegerValuesByName.insert(std::make_pair(editableIntegerValue.getName(), editableIntegerValue));
}

void EngineCreator::addEditableValue(const unsigned int lineNumber, const std::string &name, const std::string &editableValue)
{
    addEditableValue(EditableStringValue(lineNumber, name, editableValue, &editedLines[lineNumber]));
}

void EngineCreator::addEditableValue(const unsigned int lineNumber, const std::string &name, double editableValue, unsigned int decimals)
{
    addEditableValue(EditableFloatValue(lineNumber, name, shortestStringRepresentation(editableValue), &editedLines[lineNumber], decimals));
}

void EngineCreator::addEditableValue(const unsigned int lineNumber, const std::string &name, int editableValue)
{
    addEditableValue(EditableIntegerValue(lineNumber, name, shortestStringRepresentation(editableValue), &editedLines[lineNumber]));
}

unsigned int EngineCreator::getLineCount() const
{
    return linesCount;
}

auto EngineCreator::getEditableTextValuesByName() const
{
    return editableTextValuesByName;
}

auto EngineCreator::getEditableFloatValuesByName() const
{
    return editableFloatValuesByName;
}

auto EngineCreator::getEditableIntegerValuesByName() const
{
    return editableIntegerValuesByName;
}

EditableStringValue *EngineCreator::getEditableStringValue(const std::string &name)
{
    auto it = editableTextValuesByName.find(name);
    if (it == editableTextValuesByName.end())
    {
        throw EditableValueNotExistException(name);
    }
    return &it->second;
}

EditableFloatValue *EngineCreator::getEditableFloatValue(const std::string &name)
{
    auto it = editableFloatValuesByName.find(name);
    if (it == editableFloatValuesByName.end())
    {
        throw EditableValueNotExistException(name);
    }
    return &it->second;
}

EditableIntegerValue *EngineCreator::getEditableIntegerValue(const std::string &name)
{
    auto it = editableIntegerValuesByName.find(name);
    if (it == editableIntegerValuesByName.end())
    {
        throw EditableValueNotExistException(name);
    }
    return &it->second;
}
#include "EngineCreator.h"

EngineCreator::EngineCreator()
{
    std::ifstream file = std::ifstream(path + exampleEngineName);

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
        // std::cout << s << "\n";
        lines.push_back(s);
    }

    // Close the file
    file.close();
}

std::string EngineCreator::getLineFromFile(std::string fileName, unsigned int lineNumber)
{
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
        // std::cout << s << "\n";
        lines.push_back(s);
    }

    // Close the file
    file.close();
    return lines[lineNumber];
}

std::string EngineCreator::getLine(unsigned int lineNumber)
{
    return lines[lineNumber];
}

std::string EngineCreator::getLineFromCreatedFile(unsigned int lineNumber)
{
    return getLineFromFile(createdEngineName, lineNumber);
}

void EngineCreator::changeLineTo(unsigned int lineNumber, std::string newLineText)
{
    lines[lineNumber] = newLineText;
}

void EngineCreator::writeAllLinesToFile()
{
    std::ofstream file(path + createdEngineName);

    for (auto line : lines)
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

std::string EngineCreator::getAllLinesAsString()
{
    std::string allLines;
    for (auto line : lines)
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

bool EngineCreator::textExistsInLine(unsigned int lineNumber, std::string textToFind)
{
    return (lines[lineNumber].find(textToFind) != std::string::npos);
}

void EngineCreator::replaceTextInLine(unsigned int lineNumber, std::string textToReplace, std::string newText)
{
    std::string line = lines[lineNumber];

    auto &&pos = line.find(textToReplace, size_t{});
    if (pos != std::string::npos)
    {
        line.replace(pos, textToReplace.length(), newText);
        pos = textToReplace.find(textToReplace, pos + newText.length());
    }
    lines[lineNumber] = line;
}

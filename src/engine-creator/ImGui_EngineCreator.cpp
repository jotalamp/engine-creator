#include "ImGui_EngineCreator.h"

ImGui_EngineCreator::ImGui_EngineCreator()
{
    show_save_as_window = false;
    engineCreator.addEditableValue(18, "wb_ignition.rev_limit", 7500);
    engineCreator.addEditableValue(23, "wb_ignition.limiter_duration", 0.1);
    engineCreator.addEditableValue(134, "engine.name", "Audi 2.3 inline 5");
    engineCreator.addEditableValue(135, "engine.starter_torque", 200);
    engineCreator.addEditableValue(136, "engine.redline", 6000);
    engineCreator.addEditableValue(138, "fuel.max_turbulence_effect", 2.5);
    engineCreator.addEditableValue(139, "fuel.max_burning_efficiency", 0.75);
    engineCreator.addEditableValue(140, "engine.hf_gain", 0.01);
    engineCreator.addEditableValue(141, "engine.noise", 1.0);
    engineCreator.addEditableValue(142, "engine.jitter", 0.299);
    engineCreator.addEditableValue(143, "engine.simulation_frequency", 10000);

    engineCreator.addEditableValue(146, "stroke", 79.5);
    engineCreator.addEditableValue(147, "bore", 86.4);
    engineCreator.addEditableValue(148, "rod_length", 5.142);
    engineCreator.addEditableValue(149, "rod_mass", 535);
    engineCreator.addEditableValue(150, "compression_height", 32.8);
    engineCreator.addEditableValue(151, "crank_mass", 9.39);
    engineCreator.addEditableValue(152, "flywheel_mass", 6.8);
    engineCreator.addEditableValue(153, "flywheel_radius", 6);
}

void ImGui_EngineCreator::editText(const std::string &name)
{
    auto line = engineCreator.getEditableLine(name);

    if (line == nullptr)
    {
        std::cout << "\nEditbleLine: " + name + " not found!";
        exit(0);
    }

    if (ImGui::InputTextWithHint(line->getName().c_str(), line->getEditableText().c_str(), line->getEditedText()))
    {
        engineCreator.replaceTextInLine(line->getLineNumber(), line->getEditableText(), *line->getEditedText());
        setScroll(line->getLineNumber());
    }

    if ((*line->getEditedText()).size() == 0)
    {
        *line->getEditedText() = line->getEditableText();
        engineCreator.replaceTextInLine(line->getLineNumber(), line->getEditableText(), *line->getEditedText());
    }
}

void ImGui_EngineCreator::editFloat(const std::string &name, unsigned char decimals)
{
    auto line = engineCreator.getEditableFloatValue(name);

    if (line == nullptr)
    {
        std::cout << "\nEditbleLine: " + name + " not found!";
        exit(0);
    }

    char format[5] = "%.2f";
    format[2] = std::to_string(decimals)[0];

    if (ImGui::InputFloat(line->getName().c_str(), line->getEditedFloatValue(), 0.1f, 1.0f, format, ImGuiInputTextFlags_CharsDecimal))
    {
        setScroll(line->getLineNumber());
        if (*line->getEditedFloatValue() < 0)
            *line->getEditedFloatValue() = 0;
        engineCreator.replaceTextInLine(line->getLineNumber(), line->getEditableText(), line->getEditedValueAsString(decimals));
    }
}

void ImGui_EngineCreator::editInt(const std::string &name)
{
    auto line = engineCreator.getEditableIntegerValue(name);

    if (line == nullptr)
    {
        std::cout << "\nEditbleLine: " + name + " not found!";
        exit(0);
    }

    if (ImGui::InputInt(line->getName().c_str(), line->getEditedIntegerValue(), 10.0f, 100.0f, ImGuiInputTextFlags_CharsDecimal))
    {
        setScroll(line->getLineNumber());
        if (*line->getEditedIntegerValue() < 0)
            *line->getEditedIntegerValue() = 0;
        engineCreator.replaceTextInLine(line->getLineNumber(), line->getEditableText(), line->getEditedValueAsString());
    }
}

void ImGui_EngineCreator::showSaveButton()
{
    if (ImGui::Button("Save"))
    {
        engineCreator.writeAllLinesToFile();
        std::cout << "\nFile saved";
    }
}

void ImGui_EngineCreator::showEditedEngineFile()
{
    ImGui::SetNextWindowPos(ImVec2(0.4 * ImGui::GetIO().DisplaySize.x, 0));
    ImGui::SetNextWindowSize(ImVec2(0.6 * ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));

    ImGui::Begin("Edited engine file");

    if (scrollToLine)
    {
        ImGui::SetScrollY((float)lineToScroll/(float)engineCreator.getLineCount()*ImGui::GetScrollMaxY());
        scrollToLine = false;
    }
    
    ImGui::TextUnformatted(engineCreator.getAllEditedLinesAsString().c_str());

    ImGui::End();
}

void ImGui_EngineCreator::showSaveAsWindow()
{
    if (!show_save_as_window)
        return;
    ImGui::Begin("Save as", &show_save_as_window);

    ImGui::InputText("File name", newFileName, IM_ARRAYSIZE(newFileName));

    if (engineCreator.fileNameIsCorrect(newFileName))
    {
        if (ImGui::Button("Save"))
        {
            engineCreator.setCreatedEngineFileName(newFileName);
            engineCreator.writeAllLinesToFile();
            std::string textFileSaved = "Saved file '" + std::string(newFileName) + "'";
            std::cout << "\n"
                      << textFileSaved << "\n";
            show_save_as_window = false;
        }
    }
    else
    {
        ImGui::Text("Not valid name!");
    }

    ImGui::End();
}

void ImGui_EngineCreator::showInputValues()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(0.4 * ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));

    ImGui::Begin("Engine Creator"); // Create a window called "Engine Creator" and append into it.

    ImGui::PushItemWidth(150);

    editText("engine.name");
    editInt("engine.starter_torque");
    editInt("engine.redline");
    editFloat("fuel.max_turbulence_effect");
    editFloat("fuel.max_burning_efficiency");
    editFloat("engine.hf_gain");
    editFloat("engine.noise");
    editFloat("engine.jitter", 3);
    editInt("engine.simulation_frequency");

    ImGui::Separator();

    editFloat("stroke", 1);
    editFloat("bore", 1);
    editFloat("rod_length", 3);
    editInt("rod_mass");
    editFloat("compression_height", 1);
    editFloat("crank_mass", 2);
    editFloat("flywheel_mass", 1);
    editInt("flywheel_radius");

    ImGui::Separator();

    editInt("wb_ignition.rev_limit");
    editFloat("wb_ignition.limiter_duration");

    ImGui::Separator();

    ImGui::PopItemWidth();

    if (ImGui::Button("Save as"))
    {
        show_save_as_window = true;
    }
    ImGui::SameLine();
    showSaveButton();

    showSaveAsWindow();

    // ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state

    // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}

void ImGui_EngineCreator::setScroll(const unsigned int lineNumber)
{
    lineToScroll = (lineNumber + 1);
    scrollToLine = true;
}

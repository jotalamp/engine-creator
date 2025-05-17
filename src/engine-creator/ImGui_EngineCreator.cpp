#include "ImGui_EngineCreator.h"

Units::Unit convert;

ImGui_EngineCreator::ImGui_EngineCreator()
{
    show_save_as_window = false;
    engineCreator.addEditableValue(18, "wb_ignition.rev_limit", 7500);
    engineCreator.addEditableValue(23, "wb_ignition.limiter_duration", 0.1, 2);
    engineCreator.addEditableValue(134, "engine.name", "Audi 2.3 inline 5");
    engineCreator.addEditableValue(135, "engine.starter_torque", 200);
    engineCreator.addEditableValue(136, "engine.redline", 6000);
    engineCreator.addEditableValue(138, "fuel.max_turbulence_effect", 2.5, 2);
    engineCreator.addEditableValue(139, "fuel.max_burning_efficiency", 0.75, 3);
    engineCreator.addEditableValue(140, "engine.hf_gain", 0.01, 3);
    engineCreator.addEditableValue(141, "engine.noise", 1.0, 2);
    engineCreator.addEditableValue(142, "engine.jitter", 0.299);
    engineCreator.addEditableValue(143, "engine.simulation_frequency", 10000);

    engineCreator.addEditableValue(146, "stroke", 79.5, 2);
    engineCreator.addEditableValue(147, "bore", 86.4, 2);
    engineCreator.addEditableValue(148, "rod_length", 5.142);
    engineCreator.addEditableValue(149, "rod_mass", 535);
    engineCreator.addEditableValue(150, "compression_height", 32.8, 2);
    engineCreator.addEditableValue(151, "crank_mass", 9.39, 3);
    engineCreator.addEditableValue(152, "flywheel_mass", 6.8, 2);
    engineCreator.addEditableValue(153, "flywheel_radius", 6);
}

void ImGui_EngineCreator::editText(const std::string &name)
{
    auto line = engineCreator.getEditableStringValue(name);

    if (ImGui::InputTextWithHint(line->getName().c_str(), line->getEditableText().c_str(), line->getEditedValue()))
    {
        line->updateLine();
        setScroll(line->getLineNumber());
    }

    if ((*line->getEditedValue()).size() == 0)
    {
        line->setValue(line->getEditableText().c_str());
    }
}

void ImGui_EngineCreator::editFloat(const std::string &name)
{
    auto line = engineCreator.getEditableFloatValue(name);

    char format[5] = "%.2f";
    format[2] = std::to_string(line->getDecimals())[0];

    ImGui::PushItemWidth(100);

    ImGui::PushID(line->getLineNumber());

    const char *current_item = line->getUnitTypeAsString().c_str();
    if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(line->items); n++)
        {
            bool is_selected = (current_item == line->items[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(line->items[n], is_selected))
            {
                current_item = line->items[n];
                line->setUnitType(convert[current_item]);
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::PopID();
    ImGui::PopItemWidth();
    ImGui::SameLine();

    float step;
    switch (line->getDecimals())
    {
    case 0:
        step = 1.0f;
        break;
    case 1:
        step = 0.1f;
        break;
    case 2:
        step = 0.01f;
        break;
    case 3:
        step = 0.001f;
        break;
    default:
        step = 0.0001f;
        break;
    }
    const float stepFast = 100 * step;

    if (ImGui::InputFloat(line->getName().c_str(), line->getEditedFloatValue(), step, stepFast, format, ImGuiInputTextFlags_CharsDecimal))
    {
        setScroll(line->getLineNumber());
        if (*line->getEditedFloatValue() < 0)
            *line->getEditedFloatValue() = 0;

        line->updateLine();
    }
}

void ImGui_EngineCreator::editInt(const std::string &name)
{
    auto line = engineCreator.getEditableIntegerValue(name);

    ImGui::PushItemWidth(100);
    ImGui::PushID(line->getLineNumber());
    const char *current_item = line->getUnitTypeAsString().c_str();
    if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(line->items); n++)
        {
            bool is_selected = (current_item == line->items[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(line->items[n], is_selected))
            {
                current_item = line->items[n];

                line->setUnitType(convert[current_item]);
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::PopID();
    ImGui::PopItemWidth();
    ImGui::SameLine();

    unsigned int step = 1;
    if (*line->getEditedIntegerValue() < 100)
    {
        step = 1;
    }
    else if (*line->getEditedIntegerValue() < 1000)
    {
        step = 10;
    }
    else
    {
        step = 100;
    }
    const unsigned int stepFast = 10 * step;
    if (ImGui::InputInt(line->getName().c_str(), line->getEditedIntegerValue(), step, stepFast, ImGuiInputTextFlags_CharsDecimal))
    {
        setScroll(line->getLineNumber());
        if (*line->getEditedIntegerValue() < 0)
            *line->getEditedIntegerValue() = 0;

        // line->setValue(*line->getEditedIntegerValue());
        line->updateLine();
    }
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
    editFloat("engine.jitter");
    editInt("engine.simulation_frequency");

    ImGui::Separator();

    editFloat("stroke");
    editFloat("bore");
    editFloat("rod_length");
    editInt("rod_mass");
    editFloat("compression_height");
    editFloat("crank_mass");
    editFloat("flywheel_mass");
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

void ImGui_EngineCreator::showSaveButton()
{
    if (ImGui::Button("Save"))
    {
        engineCreator.writeAllLinesToFile();
        std::cout << "\nFile saved";
    }
}

void ImGui_EngineCreator::setScroll(const unsigned int lineNumber)
{
    lineToScroll = (lineNumber + 1);
    scrollToLine = true;
}

void ImGui_EngineCreator::showEditedEngineFile()
{
    ImGui::SetNextWindowPos(ImVec2(0.4 * ImGui::GetIO().DisplaySize.x, 0));
    ImGui::SetNextWindowSize(ImVec2(0.6 * ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));

    ImGui::Begin("Edited engine file");

    if (scrollToLine)
    {
        ImGui::SetScrollY((float)lineToScroll / (float)engineCreator.getLineCount() * ImGui::GetScrollMaxY());
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
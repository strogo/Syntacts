#include "Workspace.hpp"
#include "Gui.hpp"

using namespace mahi::gui;

Workspace::Workspace(Gui& gui) : Widget(gui),
                                 designer(gui),
                                 sequencer(gui),
                                 spatializer(gui)
{
}

void Workspace::update()
{
    ImGui::BeginFixed("Workspace", position, size);
    if (ImGui::BeginTabBar("WorkspaceTabs"))
    {
        if (ImGui::BeginTabItem("Designer##Tab"))
        {
            activeTab = TabDesigner;
            designer.update();
            ImGui::EndTabItem();
            gui.visualizer.setRenderedSignal(designer.buildSignal(), Purples::Plum);
        }
        if (ImGui::BeginTabItem("Sequencer##Tab"))
        {
            activeTab = TabSequencer;
            sequencer.update();
            ImGui::EndTabItem();
            gui.visualizer.setRenderedSignal(sequencer.buildSignal(), Oranges::Coral);
        }
        if (ImGui::BeginTabItem("Spatializer##Tab"))
        {
            activeTab = TabSpatializer;
            spatializer.update();
            ImGui::EndTabItem();
            gui.visualizer.setRenderedSignal(spatializer.getSignal(), Greens::YellowGreen);
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}
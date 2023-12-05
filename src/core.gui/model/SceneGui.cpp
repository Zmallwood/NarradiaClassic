#include "SceneGui.h"

namespace Narradia {
    void SceneGui::UpdateGameLogic() {
        for (auto gui_component : gui_components_)
            gui_component->UpdateGameLogic();
    }

    void SceneGui::AddGuiComponent(std::shared_ptr<GuiComponent> component) {
        gui_components_.push_back(component);
    }
}

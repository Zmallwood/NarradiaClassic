#include "SceneGui.h"

namespace Narradia {
    /**
     * Forwards the update request to all contained gui components.
     */
    void SceneGui::UpdateGameLogic() {
        for (auto gui_component : gui_components_)
            gui_component->UpdateGameLogic();
    }

    /**
     * Adds a new gui component.
     */
    void SceneGui::AddGuiComponent(std::shared_ptr<GuiComponent> component) {
        gui_components_.push_back(component);
    }
}

#include "SceneGuiView.h"

namespace Narradia {
    /**
     * Forwards the Render request to all contained gui component views.
     */
    void SceneGuiView::Render() {
        for (auto gui_component_view : gui_component_views_)
            gui_component_view->Render();
    }

    /**
     * Adds a new GuiComponentView to the internal structure, also connects it
     * with the corresponding Model component in the SceneGui.
     */
    void SceneGuiView::AddGuiComponentView(std::shared_ptr<GuiComponentView> gui_component_view) {
        auto gui_component = scene_gui_->gui_components().at(gui_component_views_.size());
        gui_component_view->set_gui_component(gui_component);
        gui_component_views_.push_back(gui_component_view);
    }
}

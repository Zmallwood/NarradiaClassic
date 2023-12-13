#include "main_scene_view.h"
#include "core.render.text/view/command/draw_string.h"
#include "core.render.text/view/command/new_string.h"
#include "main_scene.gui/view/experience_bar_view.h"
#include "main_scene.modules.world_view/view/world_view_module_view.h"
#include "main_scene.modules/view/fps_counter_module_view.h"
#include "scenes/main/model/main_scene.h"
#include "world.actors/model/player.h"
#include "main_scene.gui/view/status_panel_view.h"
namespace Narradia
{
    MainSceneView::MainSceneView() {
        scene_gui_view_->set_scene_gui(MainScene::get()->scene_gui());
        scene_gui_view_->AddGuiComponentView(std::make_shared<ExperienceBarView>());
        scene_gui_view_->AddGuiComponentView(std::make_shared<StatusPanelView>());
    }

    /**
     Render operations.
    */
    void MainSceneView::RenderDerived() {
        WorldViewModuleView::get()->Render();
        FPSCounterModuleView::get()->Render();
    }
}

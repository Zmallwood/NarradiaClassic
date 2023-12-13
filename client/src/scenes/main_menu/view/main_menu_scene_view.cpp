#include "main_menu_scene_view.h"
#include "core.gui/view/gui_button_view.h"
#include "core.render/view/command/draw_image.h"
#include "core.render/view/command/new_image.h"
#include "scenes/main_menu/model/main_menu_scene.h"
namespace Narradia
{
    /**
     Set scene gui and initialize Views for gui components
     initialize in scene model. Also prepare RenderIDs for
     images to be rendered.
    */
    MainMenuSceneView::MainMenuSceneView() {
        scene_gui_view_->set_scene_gui(MainMenuScene::get()->scene_gui());
        scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonView>());
        scene_gui_view_->AddGuiComponentView(std::make_shared<GuiButtonView>());
        rid_background = NewImage();
        rid_logo = NewImage();
    }

    /**
     Render operations.
    */
    void MainMenuSceneView::RenderDerived() {
        DrawImage("DefaultSceneBackground", rid_background, {0.0f, 0.0f, 1.0f, 1.0f});
        DrawImage("NarradiaLogo", rid_logo, {0.4f, 0.1f, 0.2f, 0.1f});
        RectF rect = {0.15f, 0.15f, 0.2f, 0.1f};
        Color color = {0, 0, 255, 255};
    }
}

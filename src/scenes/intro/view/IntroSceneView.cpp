#include "IntroSceneView.h"
#include "core.render.text/view/RendererText.h"
#include "core.render.text/view/command/DrawString.h"
#include "core.render.text/view/command/NewString.h"
#include "core.render/view/Renderer2DImagesView.h"
#include "core.render/view/command/DrawImage.h"
#include "core.render/view/command/NewImage.h"
#include "scenes/intro/model/IntroScene.h"

namespace Narradia {
    IntroSceneView::IntroSceneView() {
        scene_gui_view_->set_scene_gui(IntroScene::Get()->scene_gui());
        rid_background = NewImage();
        rid_logo = NewImage();
        rid_text = NewString();
    }

    /**
     Render operations.
    */
    void IntroSceneView::RenderDerived() {
        RectF dest_background = {0.0f, 0.0f, 1.0f, 1.0f};
        DrawImage("DefaultSceneBackground", rid_background, dest_background);
        DrawImage("NarradiaLogo", rid_logo, {0.3f, 0.1f, 0.4f, 0.2f});
        RectF rect = {0.1f, 0.1f, 0.2f, 0.1f};
        Color color = {1.0f, 0.0f, 0.0f, 255};
        if (SDL_GetTicks() % 600 > 300)
            DrawString(rid_text, "Press to start", {0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, true);
    }
}

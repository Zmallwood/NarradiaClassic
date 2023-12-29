#if 1
#include "intro_pg_v.h"
#include "render-text/cmd_v/draw_string.h"
#include "render-text/cmd_v/new_string.h"
#include "render/renderer_2d_images_v.h"
#include "intro_pg.h"
#include "gui-core_v.h"
#endif

namespace Narradia
{
   IntroPgV::IntroPgV()
   {
      scene_gui_view_->set_scene_gui(IntroPg::get()->scene_gui());
      rid_background = NewImage();
      rid_logo = NewImage();
      rid_text = NewString();
   }
   void IntroPgV::RenderDerived()
   {
      RectF dest_background = {0.0f, 0.0f, 1.0f, 1.0f};
      DrawImage("DefaultSceneBackground", rid_background, dest_background);
      DrawImage("NarradiaLogo", rid_logo, {0.3f, 0.1f, 0.4f, 0.2f});
      RectF rect = {0.1f, 0.1f, 0.2f, 0.1f};
      Color color = {1.0f, 0.0f, 0.0f, 255};
      if (SDL_GetTicks() % 600 > 300)
         DrawString(rid_text, "Press to start", {0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, true);
   }
}

#include "experience_bar_view.h"
#include "render-text/v/cmd/draw_string.h"
#include "render-text/v/cmd/new_string.h"
#include "render/v/cmd/draw_image.h"
#include "render/v/cmd/fill_rect.h"
#include "render/v/cmd/new_image.h"
#include "render/v/cmd/new_rect.h"
#include "main_scene-gui/m/experience_bar.h"
#include "world-actors/m/player.h"

namespace Narradia
{
   ExperienceBarView::ExperienceBarView()
   {
      rid_unfilled_area_ = NewRect();
      rid_filled_area_ = NewImage();
      rid_text_ = NewString();
   }

   void ExperienceBarView::Render()
   {
      auto unfilled_area =
          RectF{0.0f, 1.0f - ExperienceBar::kBarHeight, 1.0f, ExperienceBar::kBarHeight};
      FillRect(rid_unfilled_area_, unfilled_area, Colors::dark_gray);
      auto experience_progress = GetFractionalExpProgress(Player::get()->experience());
      auto filled_area = RectF{
          0.0f, 1.0f - ExperienceBar::kBarHeight, experience_progress, ExperienceBar::kBarHeight};
      DrawImage("Green", rid_filled_area_, filled_area);
      std::stringstream stream;
      stream << std::fixed << std::setprecision(2) << (experience_progress * 100) << " %";
      std::string progress_text = stream.str();
      DrawString(rid_text_, progress_text, unfilled_area.GetCenter(), Colors::white, true);
   }
}

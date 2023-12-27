#if 1
#include "status_panel_v.h"
#include "main_scene-gui/status_panel.h"
#include "render-text/cmd_v/draw_string.h"
#include "render-text/cmd_v/new_string.h"
#include "render/cmd_v/draw_image.h"
#include "render/cmd_v/fill_rect.h"
#include "render/cmd_v/new_image.h"
#include "render/cmd_v/new_rect.h"
#include "world-actors/player.h"
#endif

namespace Narradia
{
   StatusPanelV::StatusPanelV()
   {
      rid_background_image_ = NewImage();
      rid_health_text_ = NewString();
      rid_stamina_text_ = NewString();
      rid_health_bar_ = NewRect();
      rid_stamina_bar_ = NewRect();
      rid_health_bar_filled_ = NewImage();
      rid_stamina_bar_filled_ = NewImage();
      rid_player_name_ = NewString();
      rid_level_label_ = NewString();
      rid_level_ = NewString();
   }
   void StatusPanelV::Render()
   {
      auto player = Player::get();
      DrawImage("PanelBg", rid_background_image_, StatusPanel::kBoundsPanel);
      DrawString(
          rid_player_name_, player->name(),
          StatusPanel::kBoundsPanel.GetPosition().Translate(0.01f, 0.02f));
      auto level_text = std::to_string(GetCurrentLevel(player->experience()));
      DrawString(
          rid_level_label_, "Level",
          StatusPanel::kBoundsPanel.GetPosition().Translate(0.01f, 0.05f), Colors::white, false,
          FontSizes::_40);
      DrawString(
          rid_level_, level_text, StatusPanel::kBoundsPanel.GetPosition().Translate(0.06f, 0.05f),
          Colors::yellow, false, FontSizes::_40);
      DrawString(rid_health_text_, "Health", {0.01f, 0.11f});
      DrawString(rid_stamina_text_, "Stamina", {0.01f, 0.14f});
      auto hp_bar_filled_bounds = StatusPanel::kHpBarBounds.WithWidth(
          (player->health()) / player->max_health() * StatusPanel::kHpBarBounds.w);
      auto stamina_bar_filled_bounds = StatusPanel::kStaminaBarBounds.WithWidth(
          (player->stamina()) / player->max_stamina() * StatusPanel::kStaminaBarBounds.w);
      FillRect(rid_health_bar_, StatusPanel::kHpBarBounds, Colors::black);
      DrawImage("Red", rid_health_bar_filled_, hp_bar_filled_bounds);
      FillRect(rid_stamina_bar_, StatusPanel::kStaminaBarBounds, Colors::black);
      DrawImage("Yellow", rid_stamina_bar_filled_, stamina_bar_filled_bounds);
   }
}

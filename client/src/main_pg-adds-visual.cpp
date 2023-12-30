#if 1
#include "main_pg-adds-visual.h"
#include "actors.h"
#include "conf.h"
#include "core.h"
#include "main_pg-adds-world_view.h"
#include "rend-core.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   // FPSCounterModule
#if 1
   void FPSCounterAdd::UpdateGameLogic() {
      frames_count_++;
      if (SDL_GetTicks() - ticks_last_update_ > kMillisPerSecond) {
         fps_ = frames_count_;
         frames_count_ = 0;
         ticks_last_update_ = SDL_GetTicks();
      }
   }
#endif

   // KeyboardMovementModule
#if 1
   void KeyboardMovementAdd::UpdateGameLogic() {
      try {
         auto w_is_pressed = KbInput::get()->KeyIsPressed(SDLK_w);
         auto d_is_pressed = KbInput::get()->KeyIsPressed(SDLK_d);
         auto s_is_pressed = KbInput::get()->KeyIsPressed(SDLK_s);
         auto a_is_pressed = KbInput::get()->KeyIsPressed(SDLK_a);
         auto time_to_update = SDL_GetTicks() > Player::get()->ticks_last_move() +
                                                    400 / Player::get()->movement_speed();
         if (time_to_update && (w_is_pressed || d_is_pressed || s_is_pressed || a_is_pressed)) {
            if (w_is_pressed)
               Player::get()->MoveForward();
            if (d_is_pressed)
               Player::get()->MoveRight();
            if (s_is_pressed)
               Player::get()->MoveBackwards();
            if (a_is_pressed)
               Player::get()->MoveLeft();
            Player::get()->set_ticks_last_move(SDL_GetTicks());
            Player::get()->set_destination({-1, -1});
         }
      }
      catch (std::exception &e) {
         Console::get()->Print(
             "Exception in KeyboardMovementAdd::UpdateGameLogic: " + std::string(e.what()));
      }
   }
#endif

   // MouseMovementModule
#if 1
   void MouseMovementAdd::UpdateGameLogic() {
      MouseInput::get()->left_btn()->AddFiredAction(
          [] {
             Player::get()->set_destination(TileHoveringAdd::get()->hovered_tile());
          },
          5);
      auto destination = Player::get()->destination();
      if (destination.x == -1 && destination.y == -1)
         return;
      auto time_to_update =
          SDL_GetTicks() > Player::get()->ticks_last_move() + 400 / Player::get()->movement_speed();
      if (time_to_update) {
         auto dx = destination.x + 0.5f - Player::get()->position().x;
         auto dy = destination.y + 0.5f - Player::get()->position().z;
         auto abs_dx = std::abs(dx);
         auto abs_dy = std::abs(dy);
         if (abs_dx < 0.5f && abs_dy < 0.5f) {
            Player::get()->set_destination({-1, -1});
            return;
         }
         auto base_angle_deg = std::atan2(dy, dx) * 180.0f / M_PI - 90.0f;
         Player::get()->set_facing_angle_deg(-base_angle_deg);
         auto angle_deg = base_angle_deg + Player::get()->facing_angle_deg();
         Player::get()->MoveAtAngle(angle_deg);
         Player::get()->set_ticks_last_move(SDL_GetTicks());
      }
   }
#endif

// MouseRotationModule
#if 1
   void MouseRotationAdd::UpdateGameLogic() {
      MouseInput::get()->right_btn()->AddFiredAction(
          [&] {
             is_rotating_ = true;
             mouse_pos_rotation_start_ = MousePosition();
             cam_horizontal_angle_deg_rotation_start_ = Camera::get()->horizontal_angle_deg();
             cam_vertical_angle_deg_rotation_start_ = Camera::get()->vertical_angle_deg();
          },
          1);
      MouseInput::get()->right_btn()->AddReleasedAction([&] { is_rotating_ = false; });
      if (is_rotating_) {
         Cursor::get()->set_style(CursorStyles::Rotating);
         auto mouse_pos = MousePosition();
         auto dx = mouse_pos.x - mouse_pos_rotation_start_.x;
         auto dy = mouse_pos.y - mouse_pos_rotation_start_.y;
         Camera::get()->set_horizontal_angle_deg(
             cam_horizontal_angle_deg_rotation_start_ - dx * kRotationSens);
         Camera::get()->set_vertical_angle_deg(
             cam_vertical_angle_deg_rotation_start_ - dy * kRotationSens);
         Player::get()->set_facing_angle_deg(Camera::get()->horizontal_angle_deg());
      }
   }
#endif

   // SkillPerformingModule
#if 1
   void SkillPerformingAdd::UpdateGameLogic() {
      if (SDL_GetTicks() > ticks_last_skill_tick_ + 400 / skill_ticks_frequency_) {
         if (SDL_GetTicks() <
                 Player::get()->ticks_ulti_skill_start() + Player::get()->ulti_skill_duration() &&
             Player::get()->ticks_ulti_skill_start() != 0) {
            auto player_pos = Player::get()->position().GetXZ().ToIntPoint();
            auto map_area = World::get()->CurrWorldArea();
            auto r = 7;
            for (auto y = player_pos.y - r; y < player_pos.y + r; y++) {
               for (auto x = player_pos.x - r; x <= player_pos.x + r; x++) {
                  if (x < 0 || y < 0 || x >= map_area->GetWidth() || y >= map_area->GetHeight())
                     continue;
                  auto dx = x - player_pos.x;
                  auto dy = y - player_pos.y;
                  if (dx * dx + dy * dy <= r * r) {
                     map_area->GetTile(x, y)->set_tile_effect(
                         {"UltiSkillTileFire", static_cast<int>(SDL_GetTicks())});
                  }
               }
            }
         }
         ticks_last_skill_tick_ = SDL_GetTicks();
      }
   }
#endif

   // TileHoveringModule
#if 1
   void TileHoveringAdd::UpdateGameLogic() {
      auto view_matrix = CameraGL::get()->view_matrix();
      auto perspective_matrix = CameraGL::get()->perspective_matrix();
      auto mouse_position_f = MousePosition();
      auto canvas_size = CanvasSize();
      auto player_x = Player::get()->position().x;
      auto player_y = Player::get()->position().z;
      auto tile_size = kTileSize;
      auto elev_amount = kElevAmount;
      auto player_world_area_position = Player::get()->position().Multiply(kTileSize);
      auto map_area = World::get()->CurrWorldArea();
      auto mouse_world_near_plane = glm::unProject(
          glm::vec3(
              mouse_position_f.x * canvas_size.w, (1.0f - mouse_position_f.y) * canvas_size.h,
              0.0f),
          view_matrix, perspective_matrix, glm::ivec4(0, 0, canvas_size.w, canvas_size.h));
      auto mouse_world_far_plane = glm::unProject(
          glm::vec3(
              mouse_position_f.x * canvas_size.w, (1.0f - mouse_position_f.y) * canvas_size.h,
              1.0f),
          view_matrix, perspective_matrix, glm::ivec4(0, 0, canvas_size.w, canvas_size.h));
      auto world_loc = Player::get()->world_location();
      auto columns_count = 111;
      auto rows_count = 111;
      auto player_x_major = static_cast<int>(player_x);
      auto player_y_major = static_cast<int>(player_y);
      bool tile_found = false;
      auto fn_iteration = [&](int x, int y) -> bool {
         auto map_x = player_x_major + x;
         auto map_y = player_y_major + y;
         if (!map_area->IsInsideMap({map_x, map_y}))
            return false;
         auto tile_coord = Point{map_x, map_y};
         auto tile = map_area->GetTile(tile_coord);
         auto elev00 = static_cast<float>(tile->elevation());
         auto elev10 = elev00;
         auto elev11 = elev00;
         auto elev01 = elev00;
         auto tile_avg_elev = (elev00 + elev10 + elev01 + elev11) / 4.0f;
         auto coord10 = tile_coord.Translate(1, 0);
         auto coord11 = tile_coord.Translate(1, 1);
         auto coord01 = tile_coord.Translate(0, 1);
         if (map_area->IsInsideMap(coord10))
            elev10 = map_area->GetTile(coord10)->elevation();
         if (map_area->IsInsideMap(coord11))
            elev11 = map_area->GetTile(coord11)->elevation();
         if (map_area->IsInsideMap(coord01))
            elev01 = map_area->GetTile(coord01)->elevation();
         auto x0 = world_loc.x * map_area->GetWidth() * tile_size + tile_coord.x * tile_size;
         auto y0 = elev00 * elev_amount;
         auto z0 = world_loc.y * map_area->GetHeight() * tile_size + tile_coord.y * tile_size;
         auto x2 =
             world_loc.x * map_area->GetWidth() * tile_size + tile_coord.x * tile_size + tile_size;
         auto y2 = elev11 * elev_amount;
         auto z2 =
             world_loc.y * map_area->GetHeight() * tile_size + tile_coord.y * tile_size + tile_size;
         auto center = glm::vec3{(x0 + x2) / 2, (y0 + y2) / 2, (z0 + z2) / 2};
         auto closest_point =
             glm::closestPointOnLine(center, mouse_world_near_plane, mouse_world_far_plane);
         if (glm::distance(center, closest_point) < tile_size / 2) {
            hovered_tile_ = {map_x, map_y};
            tile_found = true;
            return true;
         }
         return false;
      };
      for (int y = -(rows_count - 1) / 2; y < (rows_count - 1) / 2 && !tile_found; y++) {
         for (int x = -(columns_count - 1) / 2; x < (columns_count - 1) / 2 && !tile_found; x++) {
            if (fn_iteration(x, y))
               return;
         }
      }
   }
#endif
}

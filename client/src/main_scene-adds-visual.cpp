#if 1
#include "main_scene-adds-visual.h"
#include "conf.h"
#include "core.h"
#include "actors.h"
#include "world-struct.h"
#include "render/camera_gl.h"
#include "main_scene-adds-world_view_module.h"
#include "actors.h"
#endif

namespace Narradia
{
    // FPSCounterModule
#if 1
   void FPSCounterModule::UpdateGameLogic()
   {
      frames_count_++;
      if (SDL_GetTicks() - ticks_last_update_ > kMillisPerSecond)
      {
         fps_ = frames_count_;
         frames_count_ = 0;
         ticks_last_update_ = SDL_GetTicks();
      }
   }
#endif

   // MobTargetingModule
#if 1
   void MobTargetingModule::UpdateGameLogic()
   {
      MouseInput::get()->right_btn()->AddFiredAction(
          [&]
          {
             auto map_area = World::get()->CurrMapArea();
             auto hovered_tile = TileHoveringModule::get()->hovered_tile();
             if (hovered_tile.x < 0 || hovered_tile.y < 0 ||
                 hovered_tile.x >= map_area->GetWidth() || hovered_tile.y >= map_area->GetHeight())
                return;
             auto mob = map_area->GetTile(hovered_tile.x, hovered_tile.y)->mob();
             if (mob)
             {
                targeted_mob_ = mob;
             }
             Player::get()->set_destination({-1, -1});
          },
          1);
   }
   void MobTargetingModule::ClearTarget()
   {
      targeted_mob_ = nullptr;
   }
#endif

   // KeyboardMovementModule
#if 1
   void KeyboardMovementModule::UpdateGameLogic()
   {
      auto w_is_pressed = KbInput::get()->KeyIsPressed(SDLK_w);
      auto d_is_pressed = KbInput::get()->KeyIsPressed(SDLK_d);
      auto s_is_pressed = KbInput::get()->KeyIsPressed(SDLK_s);
      auto a_is_pressed = KbInput::get()->KeyIsPressed(SDLK_a);
      auto time_to_update =
          SDL_GetTicks() > Player::get()->ticks_last_move() + 400 / Player::get()->movement_speed();
      if (time_to_update && (w_is_pressed || d_is_pressed || s_is_pressed || a_is_pressed))
      {
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
         MobTargetingModule::get()->ClearTarget();
      }
   }
#endif

   // CombatChaseMovementModule
#if 1
   void CombatChaseMovementModule::UpdateGameLogic()
   {
      auto time_to_update =
          SDL_GetTicks() > Player::get()->ticks_last_move() + 400 / Player::get()->movement_speed();
      if (false == time_to_update)
         return;
      auto targeted_mob = MobTargetingModule::get()->targeted_mob();
      if (targeted_mob)
      {
         auto map_area = World::get()->CurrMapArea();
         auto player_pos = Player::get()->position();
         auto mob_coord = map_area->mobs_mirror()->at(targeted_mob);
         auto dx = mob_coord.x - player_pos.x;
         auto dy = mob_coord.y - player_pos.z;
         auto abs_dx = std::abs(dx);
         auto abs_dy = std::abs(dy);
         if (abs_dx < 0.5f && abs_dy < 0.5f)
            return;
         auto base_angle_deg = std::atan2(dy, dx) * 180.0f / M_PI - 90.0f;
         Player::get()->set_facing_angle_deg(-base_angle_deg);
         auto angle_deg = base_angle_deg + Player::get()->facing_angle_deg();
         Player::get()->MoveAtAngle(angle_deg);
         Player::get()->set_facing_angle_deg(angle_deg);
         Player::get()->set_ticks_last_move(SDL_GetTicks());
         Player::get()->set_destination({-1, -1});
      }
   }
#endif

   // MouseMovementModule
#if 1
   void MouseMovementModule::UpdateGameLogic()
   {
      MouseInput::get()->left_btn()->AddFiredAction(
          []
          {
             Player::get()->set_destination(TileHoveringModule::get()->hovered_tile());
             MobTargetingModule::get()->ClearTarget();
          },
          5);
      auto destination = Player::get()->destination();
      if (destination.x == -1 && destination.y == -1)
         return;
      auto time_to_update =
          SDL_GetTicks() > Player::get()->ticks_last_move() + 400 / Player::get()->movement_speed();
      if (time_to_update)
      {
         auto dx = destination.x + 0.5f - Player::get()->position().x;
         auto dy = destination.y + 0.5f - Player::get()->position().z;
         auto abs_dx = std::abs(dx);
         auto abs_dy = std::abs(dy);
         if (abs_dx < 0.5f && abs_dy < 0.5f)
         {
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

   //MobMovementModule
#if 1
   void MobMovementModule::UpdateGameLogic()
   {
      auto map_area = World::get()->CurrMapArea();
      auto &mobs = *(map_area->mobs_mirror());
      for (auto it = mobs.begin(); it != mobs.end();)
      {
         auto mob = it->first;
         auto coord = it->second;
         if (SDL_GetTicks() > mob->ticks_last_move() + 400 / mob->movement_speed())
         {
            auto player_pos = Player::get()->position().GetXZ().ToIntPoint();
            auto dx = player_pos.x - coord.x;
            auto dy = player_pos.y - coord.y;
            auto aggro_range = MobsConf::get()->GetAggroRange(mob->type());
            if (aggro_range > 0)
            {
               auto r = std::sqrt(dx * dx + dy * dy);
               if (r <= aggro_range)
                  mob->AggroPlayer();
            }
            int new_x;
            int new_y;
            if (mob->aggroing_player())
            {
               auto norm_x = 0;
               auto norm_y = 0;
               auto abs_dx = std::abs(dx);
               auto abs_dy = std::abs(dy);
               if (dx)
                  norm_x = dx / abs_dx;
               if (dy)
                  norm_y = dy / abs_dy;
               new_x = coord.x + norm_x;
               new_y = coord.y + norm_y;
            }
            else
            {
               auto dx = rand() % 2 - rand() % 2;
               auto dy = rand() % 2 - rand() % 2;
               new_x = coord.x + dx;
               new_y = coord.y + dy;
            }
            if (new_x >= 0 && new_y >= 0 && new_x < map_area->GetWidth() &&
                new_y < map_area->GetHeight())
            {
               auto tile = map_area->GetTile(new_x, new_y);
               if (tile->ground() != "GroundWater")
               {
                  if (nullptr == tile->object())
                  {
                     if (nullptr == tile->mob())
                     {
                        tile->set_mob(mob);
                        map_area->GetTile(coord.x, coord.y)->set_mob(nullptr);
                        mob->set_ticks_last_move(SDL_GetTicks());
                        mobs.erase(it++);
                        mobs.insert({mob, {new_x, new_y}});
                        continue;
                     }
                  }
               }
            }
         }
         ++it;
      }
   }
#endif

// MouseRotationModule
#if 1
   void MouseRotationModule::UpdateGameLogic()
   {
      MouseInput::get()->right_btn()->AddFiredAction(
          [&]
          {
             is_rotating_ = true;
             mouse_pos_rotation_start_ = MousePosition();
             cam_horizontal_angle_deg_rotation_start_ = Camera::get()->horizontal_angle_deg();
             cam_vertical_angle_deg_rotation_start_ = Camera::get()->vertical_angle_deg();
          },
          1);
      MouseInput::get()->right_btn()->AddReleasedAction([&] { is_rotating_ = false; });
      if (is_rotating_)
      {
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
   void SkillPerformingModule::UpdateGameLogic()
   {
      if (SDL_GetTicks() > ticks_last_skill_tick_ + 400 / skill_ticks_frequency_)
      {
         if (SDL_GetTicks() <
                 Player::get()->ticks_ulti_skill_start() + Player::get()->ulti_skill_duration() &&
             Player::get()->ticks_ulti_skill_start() != 0)
         {
            auto player_pos = Player::get()->position().GetXZ().ToIntPoint();
            auto map_area = World::get()->CurrMapArea();
            auto r = 7;
            for (auto y = player_pos.y - r; y < player_pos.y + r; y++)
            {
               for (auto x = player_pos.x - r; x <= player_pos.x + r; x++)
               {
                  if (x < 0 || y < 0 || x >= map_area->GetWidth() || y >= map_area->GetHeight())
                     continue;
                  auto dx = x - player_pos.x;
                  auto dy = y - player_pos.y;
                  if (dx * dx + dy * dy <= r * r)
                  {
                     map_area->GetTile(x, y)->set_tile_effect(
                         {"UltiSkillTileFire", static_cast<int>(SDL_GetTicks())});
                     if (map_area->GetTile(x, y)->mob())
                     {
                        map_area->GetTile(x, y)->mob()->Hit(
                            map_area->GetTile(x, y)->mob()->health());
                        Player::get()->AddExperience(30);
                     }
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
   void TileHoveringModule::UpdateGameLogic()
   {
      auto view_matrix = CameraGL::get()->view_matrix();
      auto perspective_matrix = CameraGL::get()->perspective_matrix();
      auto mouse_position_f = MousePosition();
      auto canvas_size = CanvasSize();
      auto player_x = Player::get()->position().x;
      auto player_y = Player::get()->position().z;
      auto tile_size = kTileSize;
      auto elev_amount = kElevAmount;
      auto player_world_area_position = Player::get()->position().Multiply(kTileSize);
      auto map_area = World::get()->CurrMapArea();
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
      auto columns_count = 111;
      auto rows_count = 111;
      auto player_x_major = static_cast<int>(player_x);
      auto player_y_major = static_cast<int>(player_y);
      bool tile_found = false;
      auto fn_iteration = [&](int x, int y) -> bool
      {
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
         auto x0 = tile_coord.x * tile_size;
         auto y0 = elev00 * elev_amount;
         auto z0 = tile_coord.y * tile_size;
         auto x2 = tile_coord.x * tile_size + tile_size;
         auto y2 = elev11 * elev_amount;
         auto z2 = tile_coord.y * tile_size + tile_size;
         auto center = glm::vec3{(x0 + x2) / 2, (y0 + y2) / 2, (z0 + z2) / 2};
         auto closest_point =
             glm::closestPointOnLine(center, mouse_world_near_plane, mouse_world_far_plane);
         if (glm::distance(center, closest_point) < tile_size / 2)
         {
            hovered_tile_ = {map_x, map_y};
            tile_found = true;
            return true;
         }
         return false;
      };
      for (int y = -(rows_count - 1) / 2; y < (rows_count - 1) / 2 && !tile_found; y++)
      {
         for (int x = -(columns_count - 1) / 2; x < (columns_count - 1) / 2 && !tile_found; x++)
         {
            if (fn_iteration(x, y))
               return;
         }
      }
   }
#endif
}

#include "map_overview_gen_scene_controller.h"
#include "world-structure/model/world.h"
#include "world-actors/model/player.h"
namespace Narradia
{
   void MapOverViewGenSceneController::OnEnter() {
      auto map_area = World::get()->curr_map_area();
      auto x = map_area->GetWidth() / 2.0f;
      auto y = map_area->GetHeight() / 2.0f;
      Player::get()->set_position({x, 0.0f, y});
   }

   void MapOverViewGenSceneController::UpdateGameFlowDerived() {
   }
}

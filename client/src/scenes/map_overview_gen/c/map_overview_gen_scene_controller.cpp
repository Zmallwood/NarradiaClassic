#include "map_overview_gen_scene_controller.h"
#include "world-actors/m/player.h"
#include "world-struct/m/world.h"

namespace Narradia
{
   void MapOverViewGenSceneController::OnEnter()
   {
      auto map_area = World::get()->CurrMapArea();
      auto x = map_area->GetWidth() / 2.0f;
      auto y = map_area->GetHeight() / 2.0f;
      Player::get()->set_position({x, 0.0f, y});
   }

   void MapOverViewGenSceneController::UpdateGameFlowDerived()
   {
   }
}

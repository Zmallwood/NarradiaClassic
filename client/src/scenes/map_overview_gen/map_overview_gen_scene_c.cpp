#if 1
#include "map_overview_gen_scene_c.h"
#include "actors.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   void MapOverViewGenSceneC::OnEnter()
   {
      auto map_area = World::get()->CurrMapArea();
      auto x = map_area->GetWidth() / 2.0f;
      auto y = map_area->GetHeight() / 2.0f;
      Player::get()->set_position({x, 0.0f, y});
   }
   void MapOverViewGenSceneC::UpdateGameFlowDerived()
   {
   }
}

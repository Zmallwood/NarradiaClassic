#if 1
#include "mob_targeting_module.h"
#include "conf.h"
#include "core.h"
#include "tile_hovering_module.h"
#include "actors.h"
#include "world-struct.h"
#endif

namespace Narradia
{
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
}

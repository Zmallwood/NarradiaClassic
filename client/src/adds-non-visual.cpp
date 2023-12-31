#if 1
#include "adds-non-visual.h"
#include "adds-visual.h"
#include "calc.h"
#include "conf.h"
#include "core.h"
#include "gui_windows.h"
#include "player.h"
#include "world-struct.h"
#endif

namespace Narradia
{
// Model
#if 1
   // KbBindingsModule
#if 1
   void KbBindingsAdd::UpdateGameLogic() {
      if (KbInput::get()->KeyHasBeenFiredPickResult(SDLK_m)) {
         GuiWindowWorldMap::get()->ToggleVisibility();
      }
   }
#endif

   // PlayerSpawnPositioningModule
#if 1
   void PlayerSpawnPositioningAdd::SpawnAtGoodLocation() {
      Player::get()->set_world_location({2, 2});
      auto map_area = World::get()->CurrWorldArea();
      std::shared_ptr<Tile> tile;
      int x;
      int y;
      auto x_center = map_area->Width() / 2;
      auto y_center = map_area->Height() / 2;
      auto r_min = std::min(map_area->Width(), map_area->Height()) / 2;
      do {
         auto angle_deg = static_cast<float>(rand() % 360);
         x = x_center + static_cast<int>((r_min - 1) * CosDeg(angle_deg));
         y = y_center + static_cast<int>((r_min - 1) * SinDeg(angle_deg));
         tile = map_area->GetTile(x, y);
      } while (tile->ground() == "GroundWater" || tile->object() || tile->mob());
      Player::get()->set_pos({static_cast<float>(x), 0.0f, static_cast<float>(y)});
   }
#endif
#endif
}

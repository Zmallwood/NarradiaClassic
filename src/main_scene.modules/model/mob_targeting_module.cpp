#include "mob_targeting_module.h"
#include "conf/model/conf.h"
#include "core.input/model/mouse_input.h"
#include "world.actors/model/player.h"
#include "world.structure/model/world.h"
#include "tile_hovering_module.h"
namespace Narradia {
  void MobTargetingModule::UpdateGameLogic() {
    MouseInput::Get()->right_button()->AddFiredAction(
        [&] {
          auto map_area = World::Get()->curr_map_area();
          auto hovered_tile = TileHoveringModule::Get()->hovered_tile();
          if (hovered_tile.x < 0 || hovered_tile.y < 0 || hovered_tile.x >= kMapWidth ||
              hovered_tile.y >= kMapHeight)
            return;
                    auto mob =
                        map_area->GetTile(hovered_tile.x,
                        hovered_tile.y)->mob();
                    if (mob) {
                      targeted_mob_ = mob;
                    }
                    Player::Get()->set_destination({-1, -1});
        },
        1);
  }

  void MobTargetingModule::ClearTarget() {
    targeted_mob_ = nullptr;
  }
}

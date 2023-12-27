#if 1
#include "draw_mob.h"
#include "conf.h"
#include "render-models/cmd_v/draw_model.h"
#include "world-struct.h"
#include "actors.h"
#include "math.h"
#endif

namespace Narradia
{
   void DrawMob(std::shared_ptr<Tile> tile, Point coord)
   {
      auto map_area = World::get()->CurrMapArea();
      auto curr_map_location = Player::get()->world_location();
      auto tile_size = kTileSize;
      auto map_offset_x = curr_map_location.x * map_area->GetWidth() * tile_size;
      auto map_offset_y = curr_map_location.y * map_area->GetHeight() * tile_size;
      auto pos = Point3F{coord.x * kTileSize, CalcTileAverageElevation(coord), coord.y * kTileSize}
                     .Translate(0.5f, 0.0f, 0.5f)
                     .Translate(map_offset_x, 0.0f, map_offset_y);
      if (tile->mob())
      {
         DrawModel(tile->mob()->type(), 0.0f, pos, 0.0f, 0.7f);
      }
   }
}

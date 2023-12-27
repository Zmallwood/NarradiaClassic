#if 1
#include "draw_objects.h"
#include "conf/consts.h"
#include "conf/objects_conf.h"
#include "render-models/cmd_v/draw_model.h"
#include "actors/player.h"
#include "world-struct.h"
#include "comm/math_sys.h"
#endif

namespace Narradia
{
   void DrawObjects(std::shared_ptr<Tile> tile, Point coord)
   {
      if (tile->object())
      {
         auto map_area = World::get()->CurrMapArea();
         auto curr_map_location = Player::get()->world_location();
         auto tile_size = kTileSize;
         auto map_offset_x = curr_map_location.x * map_area->GetWidth() * tile_size;
         auto map_offset_y = curr_map_location.y * map_area->GetHeight() * tile_size;
         auto pos =
             Point3F{coord.x * kTileSize, CalcTileAverageElevation(coord), coord.y * kTileSize}
                 .Translate(0.5f, 0.0f, 0.5f)
                 .Translate(map_offset_x, 0.0f, map_offset_y);
         auto model_rotation = 360.0f * ((coord.x * coord.y) % 10) / 10.0f;
         auto model_scaling = 0.6f * ObjectsConf::get()->GetModelScaling(tile->object()->type());
         DrawModel(
             tile->object()->type(), SDL_GetTicks() + coord.x * coord.y * 10, pos, model_rotation,
             model_scaling);
      }
   }
}

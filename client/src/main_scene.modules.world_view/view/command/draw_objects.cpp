#include "draw_objects.h"
#include "conf.world/model/objects_conf.h"
#include "conf/model/conf.h"
#include "core.render.models/view/command/draw_model.h"
namespace Narradia
{
   void DrawObjects(std::shared_ptr<Tile> tile, Point coord) {
      if (tile->object()) {
         auto pos =
             Point3F{coord.x * kTileSize, CalcTileAverageElevation(coord), coord.y * kTileSize}
                 .Translate(0.5f, 0.0f, 0.5f);
         auto model_rotation = 360.0f * ((coord.x * coord.y) % 10) / 10.0f;
         auto model_scaling = 0.6f * ObjectsConf::get()->GetModelScaling(tile->object()->type());
         DrawModel(
             tile->object()->type(), SDL_GetTicks() + coord.x * coord.y * 10, pos, model_rotation,
             model_scaling);
      }
   }
}

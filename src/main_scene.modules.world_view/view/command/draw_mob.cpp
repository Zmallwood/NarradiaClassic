#include "draw_mob.h"
#include "conf/model/conf.h"
#include "core.render/view/renderer_models_view.h"
namespace Narradia {
  void DrawMob(std::shared_ptr<Tile> tile, Point coord) {
    auto pos = Point3F{coord.x * kTileSize, CalcTileAverageElevation(coord), coord.y * kTileSize}
                   .Translate(0.5f, 0.0f, 0.5f);
    if (tile->mob()) {
      RendererModelsView::Get()->DrawModel(tile->mob()->type(), 0.0f, pos, 0.0f, 0.7f);
    }
  }
}

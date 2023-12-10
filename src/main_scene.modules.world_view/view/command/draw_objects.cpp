#include "draw_objects.h"
#include "conf/model/configuration.h"
#include "core.render/view/renderer_models_view.h"

namespace Narradia {
  void DrawObjects(std::shared_ptr<Tile> tile, Point coord) {
    auto pos = Point3F{coord.x * kTileSize, 0.0f, coord.y * kTileSize};
    if (tile->object()) {
      RendererModelsView::Get()->DrawModel(tile->object()->type(), 0.0f, pos, 0.0f, 0.6f);
    }
  }
}

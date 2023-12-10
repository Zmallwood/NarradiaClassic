#include "draw_objects.h"
#include "conf.world/model/objects_conf.h"
#include "conf/model/conf.h"
#include "core.render/view/renderer_models_view.h"
namespace Narradia {
  void DrawObjects(std::shared_ptr<Tile> tile, Point coord) {
    if (tile->object()) {
      auto pos =
          Point3F{coord.x * kTileSize, 0.0f, coord.y * kTileSize}.Translate(0.5f, 0.0f, 0.5f);
      auto model_scaling = 0.6f * ObjectsConf::Get()->GetModelScaling(tile->object()->type());
      RendererModelsView::Get()->DrawModel(tile->object()->type(), 0.0f, pos, 0.0f, model_scaling);
    }
  }
}

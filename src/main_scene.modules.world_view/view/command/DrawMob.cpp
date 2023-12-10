#include "DrawMob.h"
#include "conf/model/Configuration.h"
#include "core.render/view/RendererModelsView.h"

namespace Narradia
{
    void DrawMob(std::shared_ptr<Tile> tile, Point coord) {
        auto pos = Point3F{coord.x * kTileSize, 0.0f, coord.y * kTileSize};
        if (tile->mob()) {
            RendererModelsView::Get()->DrawModel(tile->mob()->type(), 0.0f, pos, 0.0f, 0.4f);
        }
    }
}

#include "DoDrawObjects.h"
#include "common/system/functions/Utilities.h"
#include "core.render/view/Renderer2DImagesView.h"
#include "world.structure/model/Tile.h"

namespace Narradia {
    void DoDrawObjects(TileInfo tile_info) {
        if (tile_info.tile->object()) {
            if (tile_info.tile->object()->type() != "") {
                auto object = tile_info.tile->object();
                auto image_dim = GetTextureDimensions(object->type());
                auto width = tile_info.tile_width * image_dim.width / 60.0f;
                auto height = tile_info.tile_height * image_dim.height / 60.0f;
                auto x = tile_info.col * tile_info.tile_width +
                         tile_info.tile_width / 2 - width / 2;
                auto y = tile_info.row * tile_info.tile_height +
                         tile_info.tile_height - height;
                Renderer2DImagesView::Get()->DrawImage(
                    tile_info.tile->object()->type(), tile_info.rid_object,
                    {x, y, width, height});
            }
        }
    }
}

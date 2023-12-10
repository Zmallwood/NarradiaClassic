#include "new_tile.h"
#include "new_image_polygon.h"

namespace Narradia {
  RenderID NewTile() {
    return NewImagePolygon(4);
  }
}

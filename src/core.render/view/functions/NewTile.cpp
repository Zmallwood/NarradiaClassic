#include "NewTile.h"
#include "NewImagePolygon.h"

namespace Narradia {
    RenderId NewTile() {
        return NewImagePolygon(4);
    }
}

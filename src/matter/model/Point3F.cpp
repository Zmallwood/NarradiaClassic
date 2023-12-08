#include "Point3F.h"

namespace Narradia {
    Point3F Point3F::Translate(float dx, float dy, float dz) {
        return {x + dx, y + dy, z + dz};
    }
}

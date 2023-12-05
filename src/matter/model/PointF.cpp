#include "PointF.h"

namespace Narradia {
    PointF PointF::Translate(float dx, float dy) const {
        return {x + dx, y + dy};
    }
}

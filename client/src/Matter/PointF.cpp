#include "PointF.h"

namespace Narradia {
    PointF PointF::Translate(float dx, float dy) const {
        return {x + dx, y + dy};
    }

    Point PointF::ToIntPoint() {
        return {static_cast<int>(x), static_cast<int>(y)};
    }
}

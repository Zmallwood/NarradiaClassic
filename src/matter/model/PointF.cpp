#include "PointF.h"

namespace Narradia
{
    /**
     * Returns a translated PointF object, while not modifying this one.
     */
    PointF PointF::Translate(float dx, float dy) const { return {x + dx, y + dy}; }

    Point PointF::ToIntPoint() { return {static_cast<int>(x), static_cast<int>(y)}; }
}

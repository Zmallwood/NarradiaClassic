#include "RectF.h"

namespace Narradia {
    GLRectF RectF::ToGLRectF() const {
        return {x * 2 - 1.0f, 1.0f - y * 2, width * 2, height * 2};
    }

    RectF RectF::Translate(float dx, float dy) const {
        return {x + dx, y + dy, width, height};
    }

    PointF RectF::GetPosition() const {
        return {x, y};
    }

    PointF RectF::GetCenter() const {
        return {x + width / 2, y + height / 2};
    }

    bool RectF::Contains(PointF point) const {
        return point.x >= x && point.y >= y && point.x < x + width &&
               point.y < y + height;
    }
}

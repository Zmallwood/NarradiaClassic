#include "RectF.h"

namespace Narradia {
    GLRectF RectF::ToGLRectF() const {
        return {x * 2 - 1.0f, 1.0f - y * 2, w * 2, h * 2};
    }

    RectF RectF::Translate(float dx, float dy) const {
        return {x + dx, y + dy, w, h};
    }

    PointF RectF::GetPosition() const {
        return {x, y};
    }

    PointF RectF::GetCenter() const {
        return {x + w / 2, y + h / 2};
    }

    bool RectF::Contains(PointF point) const {
        return point.x >= x && point.y >= y && point.x < x + w && point.y < y + h;
    }

    RectF RectF::WithWidth(float w_new) const {
        return {x, y, w_new, h};
    }

    SizeF RectF::GetSize() const {
        return {w, h};
    }
}

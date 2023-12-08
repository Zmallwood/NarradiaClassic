#include "RectF.h"

namespace Narradia
{
    /**
     * Returns this object as a GLRectF type, which is in the OpenGL coordinate
     * system.
     */
    GLRectF RectF::ToGLRectF() const {

        return {x * 2 - 1.0f, 1.0f - y * 2, width * 2, height * 2};
    }

    /**
     * Returns a translated copy of this object, while not modifying this one.
     */
    RectF RectF::Translate(float dx, float dy) const {

        return {x + dx, y + dy, width, height};
    }

    /**
     * Returns only the position part of this rectangle.
     */
    PointF RectF::GetPosition() const {

        return {x, y};
    }

    /**
     * Returns the center point of this rectangle.
     */
    PointF RectF::GetCenter() const {

        return {x + width / 2, y + height / 2};
    }

    /**
     * Tells if this rectangle has a point within its boundaries.
     */
    bool RectF::Contains(PointF point) const {

        return point.x >= x && point.y >= y && point.x < x + width && point.y < y + height;
    }
}

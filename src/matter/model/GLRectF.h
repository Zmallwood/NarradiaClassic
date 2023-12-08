#pragma once

namespace Narradia {

    /**
     * Floating point rectangle type used to differentiate rectangles specified
     * in OpenGL coordinate system.
     */
    class GLRectF {
      public:
        float x = .0f;
        float y = .0f;
        float width = .0f;
        float height = .0f;
    };
}

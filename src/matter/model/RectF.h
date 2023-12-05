#pragma once
#include "GLRectF.h"

namespace Narradia {
    class RectF {
      public:
        GLRectF ToGLRectF() const;

        float x = 0.0f;
        float y = 0.0f;
        float width = 0.0f;
        float height = 0.0f;
    };
}

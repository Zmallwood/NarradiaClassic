#include "RectF.h"

namespace Narradia {
    GLRectF RectF::ToGLRectF() {
        return {x * 2 - 1.0f, 1.0f - y * 2, width * 2, height * 2};
    }
}

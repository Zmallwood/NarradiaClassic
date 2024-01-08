#pragma once

#include "Rendering_Core.h"

namespace Narradia {

    // View

#if 1
    class DrwImagesV : public RendBaseV, public Singleton<DrwImagesV> {
      public:
        DrwImagesV();
        ~DrwImagesV();

        static constexpr int kLocationPosition = 0;
        static constexpr int kLocationColor = 1;
        static constexpr int kLocationUv = 2;
    };

    // Free functions
#if 1
    Render_ID NewImage();
    void DrawImage(
        String_View image_name, Render_ID rid, const RectF &dest, Color color = Colors::white);
#endif
#endif

}

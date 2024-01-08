#pragma once

#include "Rendering_Core.h"

namespace Narradia {

    // View

#if 1
    class DrwColorsV : public RendBaseV, public Singleton<DrwColorsV> {
      public:
        DrwColorsV();
        ~DrwColorsV();

        static constexpr int kLocationPosition = 0;
        static constexpr int kLocationColor = 1;
    };

    // Free functions
#if 1
    Render_ID NewRect();
    void DrawRect(Render_ID vao_id, RectF rect, Color color);
    void FillRect(Render_ID vao_id, RectF rect, Color color);
#endif
#endif

}

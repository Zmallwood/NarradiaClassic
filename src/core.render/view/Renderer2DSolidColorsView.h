#pragma once
#include "RendererBaseView.h"

namespace Narradia {
    /**
     * Prepares resources and renders color-filled rectangles to the canvas.
     */
    class Renderer2DSolidColorsView : public RendererBaseView,
                                      public Singleton<Renderer2DSolidColorsView> {
      public:
        Renderer2DSolidColorsView();
        ~Renderer2DSolidColorsView();
        RenderId NewRect();
        void FillRect(RenderId vao_id, RectF rect, Color color);

      private:
        const int kLocationPosition = 0;
        const int kLocationColor = 1;
    };
}

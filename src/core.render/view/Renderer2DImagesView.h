#pragma once
#include "RendererBaseView.h"

namespace Narradia {
    class Renderer2DImagesView : public RendererBaseView,
                                 public Singleton<Renderer2DImagesView> {
      public:
        Renderer2DImagesView();

        ~Renderer2DImagesView();

        RenderId NewImage();

        void DrawImage(
            std::string_view image_name, RenderId rid, const RectF& dest,
            Color color = {255, 255, 255, 255}) const;

      private:
        const int kLocationPosition = 0;
        const int kLocationColor = 1;
        const int kLocationUv = 2;
    };
}

#pragma once

namespace Narradia {
    class ImageDrawingView : public Singleton<ImageDrawingView> {
      public:
        void DrawImage(std::string_view image_name, RectF rect);
    };
}
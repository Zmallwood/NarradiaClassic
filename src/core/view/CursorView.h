#pragma once

namespace Narradia {
    class CursorView : public Singleton<CursorView> {
      public:
        CursorView();

        void RenderCursor();

      private:
        RenderId rid_image;
        
        static constexpr float kCursorWidth = 0.02f;
    };
}

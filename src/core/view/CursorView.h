#pragma once

namespace Narradia {
    class CursorView : public Singleton<CursorView> {
      public:
        CursorView();

        void RenderCursor();

      private:
        static constexpr float kCursorWidth = 0.02f;
    };
}
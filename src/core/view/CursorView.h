#pragma once

namespace Narradia
{
    /**
     Replaces default system cursor with a custom one.
    */
    class CursorView : public Singleton<CursorView> {
      public:
        CursorView();
        void RenderCursor();

      private:
        RenderId rid_image;

        static constexpr float kCursorWidth = 0.02f;
    };
}

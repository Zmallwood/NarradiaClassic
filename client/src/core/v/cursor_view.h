#pragma once

namespace Narradia
{
   class CursorView : public Singleton<CursorView>
   {
     public:
      CursorView();

      auto RenderCursor() -> void;

     private:
      RenderID rid_image;

      static constexpr float kCursorWidth = 0.02f;
   };
}

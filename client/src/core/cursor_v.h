#pragma once

namespace Narradia
{
   class CursorV : public S<CursorV>
   {
     public:
      CursorV();
      void RenderCursor();

     private:
      RenderID rid_image;

      static constexpr float kCursorWidth = 0.02f;
   };
}

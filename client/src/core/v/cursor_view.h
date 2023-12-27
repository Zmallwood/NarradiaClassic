#pragma once

#include "render/v/cmd/draw_image.h"
#include "render/v/cmd/new_image.h"
#include "core/m/cursor.h"

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

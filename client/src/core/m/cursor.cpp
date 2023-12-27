#include "cursor.h"

namespace Narradia
{
   auto Cursor::ResetStyle() -> void
   {
      style_ = CursorStyles::Default;
   }

   auto Cursor::GetCursorImageName() -> std::string_view
   {
      std::string_view img_name;

      switch (style_)
      {
      case CursorStyles::Default:
         img_name = "CursorDefault";
         break;
      case CursorStyles::Hovering:
         img_name = "CursorHovering";
         break;
      case CursorStyles::Rotating:
         img_name = "CursorRotating";
         break;
      case CursorStyles::Attack:
         img_name = "CursorAttack";
         break;
      }

      return img_name;
   }
}

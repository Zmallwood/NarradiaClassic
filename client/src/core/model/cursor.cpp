#include "cursor.h"
namespace Narradia
{
   std::string_view img_name;

   auto Cursor::ResetStyle() -> void {
      cursor_style_ = CursorStyles::Default;
   }

   auto Cursor::GetCursorImageName() -> std::string_view {
      switch (Cursor::get()->cursor_style()) {
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

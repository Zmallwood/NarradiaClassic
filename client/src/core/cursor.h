#pragma once

#include "cursor_styles.h"

namespace Narradia
{
   class Cursor : public S<Cursor>
   {
     public:
      void ResetStyle();
      auto GetCursorImageName() -> std::string_view;
      auto style()
      {
         return style_;
      }
      void set_style(CursorStyles value)
      {
         style_ = value;
      }

     private:
      CursorStyles style_ = CursorStyles::Default;
   };
}

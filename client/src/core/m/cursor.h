#pragma once

#include "cursor_styles.h"

namespace Narradia
{
   class Cursor : public Singleton<Cursor>
   {
     public:
      auto ResetStyle() -> void;

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

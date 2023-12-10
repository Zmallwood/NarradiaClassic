#pragma once
#include "CursorStyles.h"

namespace Narradia {
    class Cursor : public Singleton<Cursor> {
      public:
        void ResetStyle();
        std::string_view GetCursorImageName();

        auto cursor_style() {
            return cursor_style_;
        }

        void set_cursor_style(CursorStyles value) {
            cursor_style_ = value;
        }

      private:
        CursorStyles cursor_style_ = CursorStyles::Default;
    };
}

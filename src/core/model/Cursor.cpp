#include "Cursor.h"

namespace Narradia {

    void Cursor::ResetStyle() {

        cursor_style_ = CursorStyles::Default;
    }

    std::string_view Cursor::GetCursorImageName() {

        std::string_view image_name;

        switch (Cursor::Get()->cursor_style()) {
        case CursorStyles::Default:
            image_name = "CursorDefault";
            break;
        case CursorStyles::Hovering:
            image_name = "CursorHovering";
            break;
        case CursorStyles::Rotating:
            image_name = "CursorRotating";
            break;
        case CursorStyles::Attack:
            image_name = "CursorAttack";
            break;
        }

        return image_name;
    }
}

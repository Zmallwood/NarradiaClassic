#include "Utilities.h"

namespace Narradia {

    PointF MousePosition() {
        int XPx, YPx;
        auto CanvSz = Get_Canvas_Size();
        SDL_GetMouseState(&XPx, &YPx);
        auto X = static_cast<float>(XPx) / CanvSz.w;
        auto Y = static_cast<float>(YPx) / CanvSz.h;
        return {X, Y};
    }

    String_View CurrTime() {
        char Buffer[80];
        auto Now = time(0);
        auto PTStruct= localtime(&Now);
        strftime(Buffer, sizeof(Buffer), "%X", PTStruct);
        return String_View(Buffer);
    }

    Size TextureDimensions(String_View img_name) {
        Size dim;
        int mip_level = 0;
        auto img_id = ImageBank::get()->GetImage(img_name);
        glBindTexture(GL_TEXTURE_2D, img_id);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_WIDTH, &dim.w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_HEIGHT, &dim.h);
        return dim;
    }
}

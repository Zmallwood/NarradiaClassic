#include "Canvas_Utilities.h"

namespace Narradia {

    Size Get_Canvas_Size() {
        int W, H;
        SDL_GetWindowSize(Graphics::get()->win().get(), &W, &H);
        return {W, H};
    }

    float AspectRatio() {
        auto canv_sz = Get_Canvas_Size();
        return static_cast<float>(canv_sz.w) / canv_sz.h;
    }

    float WidthToHeight(float w) {
        return w * AspectRatio();
    }

    float HeightToWidth(float h) {
        return h / AspectRatio();
    }
}

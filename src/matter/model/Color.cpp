#include "Color.h"

namespace Narradia {
    SDL_Color Color::ToSDLColor() const {
        return {
            static_cast<unsigned char>(r),
            static_cast<unsigned char>(g),
            static_cast<unsigned char>(b),
            static_cast<unsigned char>(a)};
    }
}

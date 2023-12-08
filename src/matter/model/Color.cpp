#include "Color.h"

namespace Narradia {
    /**
     * Converts Narradia Color object to SDL type.
     */
    SDL_Color Color::ToSDLColor() const {
        return {
            static_cast<unsigned char>(r * 255), static_cast<unsigned char>(g * 255),
            static_cast<unsigned char>(b * 255), static_cast<unsigned char>(a * 255)};
    }
}

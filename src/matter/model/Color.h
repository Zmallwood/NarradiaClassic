#pragma once

namespace Narradia {
    /**
     * Contains RGBA-color data, each component ranging between 0-255.
     */
    class Color {
      public:
        SDL_Color ToSDLColor() const;

        int r = 0;
        int g = 0;
        int b = 0;
        int a = 0;
    };
}

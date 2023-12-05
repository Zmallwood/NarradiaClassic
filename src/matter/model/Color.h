#pragma once

namespace Narradia {
    /**
     * Contains RGBA-color data, each component ranging between 0-1.
     */
    class Color {
      public:
        SDL_Color ToSDLColor() const;

        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 0.0f;
    };
}

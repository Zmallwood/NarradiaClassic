#pragma once
namespace Narradia
{
    /**
     Contains RGBA-color data, each component ranging between
     0-1.
    */
    class Color {
      public:
        SDL_Color ToSDLColor() const;

        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;
    };
}

#include "Utilities.h"
#include "core.assets/model/ImageBank.h"

namespace Narradia {
    /**
     * Returns normalized mouse position.
     */
    PointF GetMousePosition() {
        int xPixels;
        int yPixels;
        auto canvasSize = GetCanvasSize();
        SDL_GetMouseState(&xPixels, &yPixels);
        auto x = static_cast<float>(xPixels) / canvasSize.width;
        auto y = static_cast<float>(yPixels) / canvasSize.height;
        return {x, y};
    }

    /**
     * Returns the current time in text format.
     */
    std::string_view GetCurrTime() {
        time_t now = time(0);
        char buffer[80];
        auto p_tstruct = localtime(&now);
        strftime(buffer, sizeof(buffer), "%X", p_tstruct);
        return buffer;
    }

    /**
     * Returns texture, loaded from file system, dimensions in pixels.
     */
    Size GetTextureDimensions(std::string_view image_name) {
        Size dimensions;
        int miplevel = 0;
        auto image_id = ImageBank::Get()->GetImage(image_name);
        glBindTexture(GL_TEXTURE_2D, image_id);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &dimensions.width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &dimensions.height);
        return dimensions;
    }
}

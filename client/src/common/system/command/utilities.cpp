#include "utilities.h"
#include "core.assets/model/image_bank.h"
namespace Narradia
{
    /**
     * @brief Get mouses position on canvas.
     *
     * @return Mouse position with coordinates ranging from 0-1.
     */
    PointF GetMousePosition() {
        int x_px, y_px;
        auto canv_sz = GetCanvasSize();
        SDL_GetMouseState(&x_px, &y_px);
        auto x = static_cast<float>(x_px) / canv_sz.w;
        auto y = static_cast<float>(y_px) / canv_sz.h;
        return {x, y};
    }

    /**
     * @brief Gets current time in text format.
     *
     */
    std::string_view GetCurrTime() {
        time_t now = time(0);
        char buffer[80];
        auto p_tstruct = localtime(&now);
        strftime(buffer, sizeof(buffer), "%X", p_tstruct);
        return std::string_view(buffer);
    }

    /**
     * @brief Gets texture dimensions in pixels.
     *
     * @param[in] image_name Name of image to measure.
     * @return Texture dimension in pixels.
     */
    Size GetTextureDimensions(std::string_view image_name) {
        Size dim;
        int mip_level = 0;
        auto image_id = ImageBank::Get()->GetImage(image_name);
        glBindTexture(GL_TEXTURE_2D, image_id);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_WIDTH, &dim.w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_HEIGHT, &dim.h);
        return dim;
    }
}

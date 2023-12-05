#pragma once
#include "core.render.text/model/FontSizes.h"

namespace Narradia {
    class Font;

    class RendererText : public Singleton<RendererText> {
      public:
        RendererText();

        RenderId NewString();

        void DrawString(
            RenderId rid, std::string_view text, PointF position,
            Color color = {1.0f, 1.0f, 1.0f, 1.0f}, bool center_align = false,
            FontSizes font_size = FontSizes::_20);

      private:
        void RenderText(
            RenderId rid, std::string_view text, Color color, bool center_align,
            FontSizes font_size, std::string &out_unique_name_id,
            SizeF &out_size) const;

        std::string CreateGetBlankTexture();

        const std::string kRelFontsPath = "Resources/Fonts/";
        const Color kOutlineColor = {0.0f, 0.0f, 0.0f, 1.0f};
        std::map<FontSizes, std::shared_ptr<Font>> fonts_;
        std::map<RenderId, std::string> unique_name_ids_;
    };
}

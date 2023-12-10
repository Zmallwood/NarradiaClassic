#pragma once
#include "core.render.text/model/font_sizes.h"

namespace Narradia {
  class Font;

  /**
   Prepares resources for, and renders, text strings as
   either 2D surfaces or 3D billboards.
  */
  class RendererText : public Singleton<RendererText> {
   public:
    RendererText();
    void RenderText(
        RenderID rid, std::string_view text, Color color, bool center_align, FontSizes font_size,
        std::string &out_unique_name_id, SizeF &out_size) const;

    auto fonts() {
      return fonts_;
    }

    auto unique_name_ids() {
      return unique_name_ids_;
    }

   private:
    const std::string kRelFontsPath = "Resources/Fonts/";
    const Color kOutlineColor = {0.0f, 0.0f, 0.0f, 1.0f};
    std::map<FontSizes, std::shared_ptr<Font>> fonts_;
    std::shared_ptr<std::map<RenderID, std::string>> unique_name_ids_;
  };
}
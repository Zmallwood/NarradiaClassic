#pragma once
#include "../../core.assets/model/image_bank.h"
#include "../../core.render/view/command/draw_image.h"
#include "../../core.render/view/command/new_image.h"
#include "../../matter/model/color.h"
#include "../model/font.h"
#include "../model/font_sizes.h"
#include <map>
#include <memory>
#include <string>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Prepares resources for, and renders, text strings as either 2D surfaces or 3D
   /// billboards.
   ////////////////////////////////////////////////////////////////////////////////
   class RendererText : public Singleton<RendererText> {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Initializes Font objects for desired sizes.
      ////////////////////////////////////////////////////////////////////////////////
      RendererText();

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Does the core rendering work for a string to be rendered to the canvas. Can be
      /// shared for both 2D string rendering and 3D billboard rendering.
      ///
      /// @param[in] rid RID for string to render.
      /// @param[in] text Text to render.
      /// @param[in] color Color of rendered text.
      /// @param[in] If the text should be center aligned at position.
      /// @param[in] font_size Font size to render with.
      /// @param[out] out_unique_name_id Will be stored with unique name for created texture.
      /// @param[out] out_size Will be stored with dimensions of the rendered text.
      ////////////////////////////////////////////////////////////////////////////////
      auto RenderText(
          RenderID rid, std::string_view text, Color color, bool center_align, FontSizes font_size,
          std::string &out_unique_name_id, SizeF &out_size) const -> void;

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

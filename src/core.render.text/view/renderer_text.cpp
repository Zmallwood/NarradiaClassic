#include "renderer_text.h"
#include "command/create_get_blank_texture.h"
#include "core.assets/model/image_bank.h"
#include "core.render.text/model/font.h"
#include "core.render/view/renderer_2d_images_view.h"
#include "core.render/view/command/draw_image.h"
#include "core.render/view/command/new_image.h"

namespace Narradia {
  /**
   Initializes Font objects for desired sizes.
  */
  RendererText::RendererText()
      : unique_name_ids_(std::make_shared<std::map<RenderID, std::string>>()) {
    TTF_Init();
    auto font_path =
        std::string(SDL_GetBasePath()) + kRelFontsPath + "PartyConfettiRegular-eZOn3.ttf";
    fonts_.insert({FontSizes::_20, std::make_shared<Font>(font_path.c_str(), 20)});
    fonts_.insert({FontSizes::_26, std::make_shared<Font>(font_path.c_str(), 26)});
  }

  /**
   Does the core rendering work for a string to be rendered
   to the canvas. Can be shared for both 2D string rendering
   and 3D billboard string rendering.
  */
  void RendererText::RenderText(
      RenderID rid, std::string_view text, Color color, bool center_align, FontSizes font_size,
      std::string &out_unique_name_id, SizeF &out_size) const {
    auto font = fonts_.at(font_size)->SDL_font().get();
    if (!font)
      return;
    auto sdl_color = color.ToSDLColor();
    auto outline_sdl_color = kOutlineColor.ToSDLColor();
    auto text_outline_surface = TTF_RenderText_Blended(
        fonts_.at(font_size)->outline_SDL_font().get(), text.data(), outline_sdl_color);
    if (!text_outline_surface)
      return;
    auto text_surface = TTF_RenderText_Blended(font, text.data(), sdl_color);
    glEnable(GL_TEXTURE_2D);
    auto unique_name_id = unique_name_ids_->at(rid);
    auto image_id = ImageBank::Get()->GetImage(unique_name_id.c_str());
    glBindTexture(GL_TEXTURE_2D, image_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    auto w = text_outline_surface->w;
    auto h = text_outline_surface->h;
    auto image = SDL_CreateRGBSurface(
        SDL_SWSURFACE, w, h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    auto area = SDL_Rect{
        Font::kFontOutlineWidth, Font::kFontOutlineWidth, text_surface ? text_surface->w : 0,
        text_surface ? text_surface->h : 0};
    auto area_outline = SDL_Rect{
        0, 0, text_outline_surface ? text_outline_surface->w : 0,
        text_outline_surface ? text_outline_surface->h : 0};
    SDL_BlitSurface(text_outline_surface, &area, image, &area_outline);
    SDL_BlitSurface(text_surface, &area_outline, image, &area_outline);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    auto canvas_size = GetCanvasSize();
    auto width = text_surface ? static_cast<float>(text_surface->w) / canvas_size.width : 0;
    auto height = text_surface ? static_cast<float>(text_surface->h) / canvas_size.height : 0;
    out_unique_name_id = unique_name_id;
    out_size = {width, height};
    SDL_FreeSurface(image);
    SDL_FreeSurface(text_surface);
    SDL_FreeSurface(text_outline_surface);
  }
}

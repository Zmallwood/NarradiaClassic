#if 1
#include "rend_text.h"
#include "conf.h"
#include "assets.h"
#include "core.h"
#include "rend_2d_images_v.h"
#endif

namespace Narradia
{
   // RendText
#if 1
   RendText::RendText()
       : unique_name_ids_(std::make_shared<std::map<RenderID, std::string>>()) {
      TTF_Init();
      auto font_path =
          std::string(SDL_GetBasePath()) + kRelFontsPath + "PartyConfettiRegular-eZOn3.ttf";
      fonts_.insert({FontSizes::_20, std::make_shared<Font>(font_path.c_str(), 20)});
      fonts_.insert({FontSizes::_40, std::make_shared<Font>(font_path.c_str(), 40)});
   }
   RendText::~RendText() {
      if (kVerbose)
         std::cout << "Disposing RendText.\n";
   }
   void RendText::RenderText(
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
      auto image_id = ImageBank::get()->GetImage(unique_name_id.c_str());
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
          GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
          image->pixels);
      auto canvas_size = CanvasSize();
      auto width = text_surface ? static_cast<float>(text_surface->w) / canvas_size.w : 0;
      auto height = text_surface ? static_cast<float>(text_surface->h) / canvas_size.h : 0;
      out_unique_name_id = unique_name_id;
      out_size = {width, height};
      SDL_FreeSurface(image);
      SDL_FreeSurface(text_surface);
      SDL_FreeSurface(text_outline_surface);
   }
#endif

   // Font
#if 1
   Font::Font(std::string_view font_file_name, int font_size) {
      SDL_font_ =
          std::shared_ptr<TTF_Font>(TTF_OpenFont(font_file_name.data(), font_size), SDLDeleter());
      outline_SDL_font_ =
          std::shared_ptr<TTF_Font>(TTF_OpenFont(font_file_name.data(), font_size), SDLDeleter());
      TTF_SetFontOutline(outline_SDL_font_.get(), kFontOutlineWidth);
   }
#endif

// Free functions
#if 1
   auto NewString() -> RenderID {
      static int id_counter = 0;
      auto id = id_counter++;
      auto unique_name = "RenderedImage" + std::to_string(id);
      ImageBank::get()->CreateBlankTextImage(unique_name);
      auto rendid_image_rect = NewImage();
      RendText::get()->unique_name_ids()->insert({rendid_image_rect, unique_name});
      return rendid_image_rect;
   }
   auto DrawString(
       RenderID rid, std::string_view text, PointF position, Color color, bool center_align,
       FontSizes font_size) -> void {
      std::string unique_name_id;
      SizeF size;
      RendText::get()->RenderText(
          rid, text, color, center_align, font_size, unique_name_id, size);
      auto canvas_size = CanvasSize();
      auto rect = RectF{position.x, position.y, size.w, size.h};
      int text_w;
      int text_h;
      TTF_SizeText(
          RendText::get()->fonts().at(font_size)->SDL_font().get(), text.data(), &text_w,
          &text_h);
      rect.y -= static_cast<float>(text_h / AspectRatio()) / canvas_size.h / 2.0f;
      if (center_align)
         rect.x -=
             static_cast<float>(text_w) / static_cast<float>(canvas_size.h) / 2.0f / AspectRatio();
      DrawImage(unique_name_id, rid, rect);
   }
#endif
}

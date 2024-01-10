#include "TextRendering.h"
#include "Core/Assets/nModelBank.h"
#include "Core/Core.h"
#include "ImagesRendering.h"
#include "Core/Assets/nImageBank.h"
#include "Conf/Constants.h"

namespace Narradia {

   // View

#if 1
   // DrwText
#if 1
   DrwTextV::DrwTextV()
       : unique_name_ids_(MakeShared<std::map<RenderID, std::string>>()) {
      TTF_Init();

      auto font_path = String(SDL_GetBasePath()) + kRelFontsPath + "PartyConfettiRegular-eZOn3.ttf";

      fonts_.insert({FontSizes::_20, MakeShared<Font>(font_path.c_str(), 20)});
      fonts_.insert({FontSizes::_40, MakeShared<Font>(font_path.c_str(), 40)});
   }

   DrwTextV::~DrwTextV() {
      if (k_verbose)
         std::cout << "Disposing DrwText.\n";
   }

   void DrwTextV::RenderText(
       RenderID rid, StringView text, Color color, bool center_align, FontSizes font_size,
       String &out_unique_name_id, SizeF &out_size) const {
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
   Font::Font(StringView font_file_name, int font_size) {
      SDL_font_ = SharedPtr<TTF_Font>(TTF_OpenFont(font_file_name.data(), font_size), SDLDeleter());

      outline_SDL_font_ =
          SharedPtr<TTF_Font>(TTF_OpenFont(font_file_name.data(), font_size), SDLDeleter());

      TTF_SetFontOutline(outline_SDL_font_.get(), kFontOutlineWidth);
   }
#endif

// Free functions
#if 1
   RenderID NewString() {
      static int id_counter = 0;

      auto id = id_counter++;
      auto unique_name = "RenderedImage" + ToString(id);
      ImageBank::get()->CreateBlankTextImage(unique_name);
      auto rendid_image_rect = NewImage();
      DrwTextV::get()->unique_name_ids()->insert({rendid_image_rect, unique_name});

      return rendid_image_rect;
   }

   void DrawString(
       RenderID rid, StringView text, PointF position, Color color, bool center_align,
       FontSizes font_size) {
      String unique_name_id;
      SizeF size;
      DrwTextV::get()->RenderText(rid, text, color, center_align, font_size, unique_name_id, size);
      auto canvas_size = CanvasSize();
      auto rect = RectF{position.x, position.y, size.w, size.h};
      int text_w;
      int text_h;
      TTF_SizeText(
          DrwTextV::get()->fonts().at(font_size)->SDL_font().get(), text.data(), &text_w, &text_h);
      rect.y -= static_cast<float>(text_h / AspectRatio()) / canvas_size.h / 2.0f;

      if (center_align)
         rect.x -=
             static_cast<float>(text_w) / static_cast<float>(canvas_size.h) / 2.0f / AspectRatio();

      DrawImage(unique_name_id, rid, rect);
   }
#endif
#endif

}

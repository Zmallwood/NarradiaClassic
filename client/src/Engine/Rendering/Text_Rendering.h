#pragma once

namespace Narradia {

    // View

#if 1
    enum class FontSizes { _20, _40 };

    class Font;

    class DrwTextV : public Singleton<DrwTextV> {
      public:
        DrwTextV();
        ~DrwTextV();
        void RenderText(
            Render_ID rid, String_View text, Color color, bool center_align, FontSizes font_size,
            String &out_unique_name_id, SizeF &out_size) const;

        auto fonts() {
            return fonts_;
        }

        auto unique_name_ids() {
            return unique_name_ids_;
        }

      private:
        const String kRelFontsPath = "Resources/Fonts/";
        const Color kOutlineColor = {0.0f, 0.0f, 0.0f, 1.0f};
        Map<FontSizes, Shared_Ptr<Font>> fonts_;
        Shared_Ptr<Map<Render_ID, String>> unique_name_ids_;
    };

    // Belonging Font class
#if 1
    class Font {
      public:
        Font(String_View font_file_name, int font_size);

        auto SDL_font() {
            return SDL_font_;
        }

        auto outline_SDL_font() {
            return outline_SDL_font_;
        }

        static constexpr int kFontOutlineWidth = 2;

      private:
        Shared_Ptr<TTF_Font> SDL_font_;
        Shared_Ptr<TTF_Font> outline_SDL_font_;
    };
#endif

    // Free functions
#if 1
    Render_ID NewString();
    void DrawString(
        Render_ID rid, String_View text, PointF position, Color color = Colors::white,
        bool center_align = false, FontSizes font_size = FontSizes::_20);
#endif
#endif

}

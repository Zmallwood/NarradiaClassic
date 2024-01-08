#pragma once

#include "Engine/Gui_Core/Gui_Core.h"

namespace Narradia {

    // Model

#if 1
// Gui components
#if 1
#if 1
    class StatusPanel : public GuiComponent, public Singleton<StatusPanel> {
      public:
        void UpdateGameLogic() override;

        static constexpr RectF kBoundsPanel = {0.0f, 0.0f, 0.2f, 0.18f};
        static constexpr RectF kHpBarBounds = {0.08f, 0.11f, 0.1f, 0.01f};
        static constexpr RectF kStaminaBarBounds = {0.08f, 0.14f, 0.1f, 0.01f};
    };

    class ExperienceBar : public GuiComponent {
      public:
        void UpdateGameLogic() override;

        static constexpr float kBarHeight = 0.025f;
    };
#endif
#endif

// Gui windows
#if 1
#if 1
    class GuiWindowWorldMap : public GuiWindow, public Singleton<GuiWindowWorldMap> {
      public:
        GuiWindowWorldMap()
            : GuiWindow("World Map", {0.3f, 0.2f, 0.5f, 0.5f}) {
        }

      private:
        void UpdateGameLogicDerived() override;
    };
#endif
#endif

    // View
#if 1
// Gui components
#if 1
    class StatusPanelV : public GuiComponentV {
      public:
        StatusPanelV();
        void Render() override;

      private:
        Render_ID rid_background_image_;
        Render_ID rid_health_text_;
        Render_ID rid_stamina_text_;
        Render_ID rid_health_bar_;
        Render_ID rid_health_bar_filled_;
        Render_ID rid_stamina_bar_;
        Render_ID rid_stamina_bar_filled_;
        Render_ID rid_player_name_;
        Render_ID rid_level_label_;
        Render_ID rid_level_;
    };

    class ExperienceBarV : public GuiComponentV {
      public:
        ExperienceBarV();
        void Render() override;

      private:
        Render_ID rid_unfilled_area_;
        Render_ID rid_filled_area_;
        Render_ID rid_text_;
    };
#endif

// Gui windows
#if 1
    class GuiWindowWorldMapV : public GuiWindowV {
      public:
        GuiWindowWorldMapV();

        auto tex_id() {
            return tex_id_;
        }

      private:
        void RenderDerived() override;

        Render_ID rid_img_;
        GLuint tex_id_ = -1;
        Vector<Render_ID> rids_rectangles_;
        Vector<Render_ID> rids_images_;
        Render_ID rid_player_;
        Render_ID rid_player_outline_;
    };
#endif
#endif
#endif

}

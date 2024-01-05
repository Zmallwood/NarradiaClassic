#pragma once

#include "Gui_Core.h"

namespace Narradia
{

   // Model
#if 1
// Gui components
#if 1
#if 1
   class StatusPanel : public GuiComponent, public S<StatusPanel> {
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
   class GuiWindowWorldMap : public GuiWindow, public S<GuiWindowWorldMap> {
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
      RenderID rid_background_image_;
      RenderID rid_health_text_;
      RenderID rid_stamina_text_;
      RenderID rid_health_bar_;
      RenderID rid_health_bar_filled_;
      RenderID rid_stamina_bar_;
      RenderID rid_stamina_bar_filled_;
      RenderID rid_player_name_;
      RenderID rid_level_label_;
      RenderID rid_level_;
   };

   class ExperienceBarV : public GuiComponentV {
     public:
      ExperienceBarV();
      void Render() override;

     private:
      RenderID rid_unfilled_area_;
      RenderID rid_filled_area_;
      RenderID rid_text_;
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

      RenderID rid_img_;
      GLuint tex_id_ = -1;
      Vec<RenderID> rids_rectangles_;
      Vec<RenderID> rids_images_;
      RenderID rid_player_;
      RenderID rid_player_outline_;
   };
#endif
#endif
#endif

}

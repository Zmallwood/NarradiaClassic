#pragma once
#include "../../matter/model/rectf.h"
#include "gui_movable_container.h"
#include "gui_window_close_button.h"
#include <string_view>
namespace Narradia
{
   class GuiWindow : public GuiMovableContainer {
     public:
      GuiWindow(
          std::string_view title, RectF bounds, bool destroy_on_close = false,
          std::string_view background_image_name = "PanelBg");

      void Hide();

      void ToggleVisibility();

      RectF AbsTitleBarBounds();

      auto destroy_on_close() {
         return destroy_on_close_;
      }

      auto visible() {
         return visible_;
      }

      auto background_image_name() {
         return background_image_name_;
      }

      auto title() {
         return title_;
      }

      auto gui_window_close_button() {
         return gui_window_close_button_;
      }

      static constexpr float kTitleBarHeight = 0.03f;
      static constexpr float kMargin = 0.005f;

     protected:
      void UpdateGameLogic() override;

     private:
      virtual void UpdateGameLogicDerived() = 0;

      std::string_view title_ = "Unnamed window";
      bool visible_ = false;
      bool destroy_on_close_ = false;
      std::shared_ptr<GuiWindowCloseButton> gui_window_close_button_;
      std::string_view background_image_name_;
   };
}

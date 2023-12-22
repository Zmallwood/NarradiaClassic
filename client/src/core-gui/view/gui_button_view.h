#pragma once
#include "core-gui/model/gui_button.h"
#include "core-render-text/view/command/draw_string.h"
#include "core-render-text/view/command/new_string.h"
#include "core-render/view/command/draw_image.h"
#include "core-render/view/command/new_image.h"
#include "gui_component_view.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief View component of the GuiButton.
   ////////////////////////////////////////////////////////////////////////////////
   class GuiButtonView : public GuiComponentView {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Prepares RIDs for rendering.
      ////////////////////////////////////////////////////////////////////////////////
      GuiButtonView();

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Renders the GuiButton to the canvas, taking into account if its hovered or not.
      ////////////////////////////////////////////////////////////////////////////////
      auto Render() -> void override;

     private:
      RenderID rid_image;
      RenderID rid_label_text_;
   };
}

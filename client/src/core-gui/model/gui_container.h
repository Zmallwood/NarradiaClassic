#pragma once
#include "../../matter/model/pointf.h"
#include "../../matter/model/rectf.h"
#include "../../matter/model/sizef.h"
#include "gui_component.h"
#include <memory>
#include <vector>
namespace Narradia
{
   class GuiContainer : public GuiComponent {
     public:
      GuiContainer(PointF position, SizeF size)
          : position_(position),
            size_(size),
            gui_components_(std::make_shared<std::vector<std::shared_ptr<GuiComponent>>>()) {
      }

      void AddGuiComponent(std::shared_ptr<GuiComponent> comp);

      RectF Bounds();

      auto position() {
         return position_;
      }

      auto size() {
         return size_;
      }

      auto gui_components() {
         return gui_components_;
      }

     protected:
      void UpdateGameLogic() override;

      void set_position(PointF value) {
         position_ = value;
      }

     private:
      PointF position_;
      SizeF size_;
      std::shared_ptr<std::vector<std::shared_ptr<GuiComponent>>> gui_components_;
   };
}

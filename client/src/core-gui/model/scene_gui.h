#pragma once
#include "gui_component.h"
#include <memory>
#include <vector>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Model component for SceneGui, of which every Scene has an inherited member instance
   /// of.
   ////////////////////////////////////////////////////////////////////////////////
   class SceneGui {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Create internal structure.
      ////////////////////////////////////////////////////////////////////////////////
      SceneGui()
          : gui_components_(std::make_shared<std::vector<std::shared_ptr<GuiComponent>>>()) {
      }
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Forwards the update request to all contained gui components.
      ////////////////////////////////////////////////////////////////////////////////
      auto UpdateGameLogic() -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Adds a new gui component to this scene.
      ///
      /// @param[in] component Component to add.
      ////////////////////////////////////////////////////////////////////////////////
      auto AddGuiComponent(std::shared_ptr<GuiComponent> comp) -> void;

      auto RemoveGuiComponent(std::shared_ptr<GuiComponent> comp) -> void;

      auto gui_components() {
         return gui_components_;
      }

     private:
      std::shared_ptr<std::vector<std::shared_ptr<GuiComponent>>> gui_components_;
   };
}

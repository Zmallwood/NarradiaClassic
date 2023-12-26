#pragma once
#include "../../core-gui/v/scene_gui_view.h"
namespace Narradia
{
   class ISceneView
   {
     public:
      ISceneView()
          : scene_gui_view_(std::make_shared<SceneGuiView>())
      {
      }

      auto Render() -> void;

     protected:
      virtual auto RenderDerived() -> void = 0;

      std::shared_ptr<SceneGuiView> scene_gui_view_;
   };
}

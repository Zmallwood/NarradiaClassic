#pragma once

namespace Narradia
{
   class SceneGuiView;

   class ISceneView
   {
     public:
      ISceneView();

      auto Render() -> void;

     protected:
      virtual auto RenderDerived() -> void = 0;

      std::shared_ptr<SceneGuiView> scene_gui_view_;
   };
}

#pragma once

namespace Narradia
{
   class SceneGuiV;

   class ISceneV
   {
     public:
      ISceneV();
      void Render();

     protected:
      virtual void RenderDerived() = 0;

      std::shared_ptr<SceneGuiV> scene_gui_view_;
   };
}

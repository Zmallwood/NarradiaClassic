#pragma once

#include "core/v/iscene_view.h"

namespace Narradia
{
   class MainMenuSceneView : public ISceneView, public Singleton<MainMenuSceneView>
   {
     public:
      MainMenuSceneView();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
   };
}

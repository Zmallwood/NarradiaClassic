#pragma once

#include "core/iscene_v.h"

namespace Narradia
{
   class MainMenuSceneV : public ISceneV, public S<MainMenuSceneV>
   {
     public:
      MainMenuSceneV();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
   };
}

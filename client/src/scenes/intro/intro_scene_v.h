#pragma once

#include "core/iscene_v.h"

namespace Narradia
{
   class IntroSceneV : public ISceneV, public S<IntroSceneV>
   {
     public:
      IntroSceneV();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
      RenderID rid_text;
   };
}

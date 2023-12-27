#pragma once

#include "core/iscene_v.h"

namespace Narradia
{
   class MainSceneV : public ISceneV, public S<MainSceneV>
   {
     public:
      MainSceneV();

     private:
      void RenderDerived() override;
   };
}

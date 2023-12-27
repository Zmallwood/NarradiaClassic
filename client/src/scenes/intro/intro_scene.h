#pragma once

#include "core/iscene.h"

namespace Narradia
{
   class IntroScene : public IScene, public S<IntroScene>
   {
     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override
      {
      }
   };
}

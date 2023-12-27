#pragma once

#include "core/iscene.h"

namespace Narradia
{
   class MainScene : public IScene, public S<MainScene>
   {
     public:
      MainScene();

     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override
      {
      }
   };
}

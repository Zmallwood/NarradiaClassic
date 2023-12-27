#pragma once

#include "core.h"

namespace Narradia
{
   class MainMenuScene : public IScene, public S<MainMenuScene>
   {
     public:
      MainMenuScene();

     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override
      {
      }
   };
}

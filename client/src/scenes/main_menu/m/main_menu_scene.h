#pragma once

#include "core/m/iscene.h"

namespace Narradia
{
   class MainMenuScene : public IScene, public Singleton<MainMenuScene>
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

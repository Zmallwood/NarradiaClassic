#pragma once
#include "core/m/iscene.h"
namespace Narradia
{
   class IntroScene : public IScene, public Singleton<IntroScene>
   {
     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override
      {
      }
   };
}

#pragma once

#include "core.h"

namespace Narradia
{
   class MainMenuPg : public IPage, public S<MainMenuPg>
   {
     public:
      MainMenuPg();

     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override
      {
      }
   };
}

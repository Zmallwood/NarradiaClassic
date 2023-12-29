#pragma once

#include "core.h"

namespace Narradia
{
   class MainPg : public IPage, public S<MainPg>
   {
     public:
      MainPg();

     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override
      {
      }
   };
}

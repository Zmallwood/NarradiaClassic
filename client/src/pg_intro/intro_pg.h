#pragma once

#include "core.h"

namespace Narradia
{
   class IntroPg: public IPage, public S<IntroPg>
   {
     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override
      {
      }
   };
}

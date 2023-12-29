#pragma once

#include "core_c.h"

namespace Narradia
{
   class MainPgC : public IPageC, public S<MainPgC>
   {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };
}

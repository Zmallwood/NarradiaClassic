#pragma once

#include "core_c.h"

namespace Narradia
{
   class IntroPgC : public IPageC, public S<IntroPgC>
   {
     private:
      void OnEnter() override;
      void UpdateGameFlowDerived() override;
   };
}

#pragma once

#include "core_c.h"

namespace Narradia
{
   class MainMenuPgC : public IPageC, public S<MainMenuPgC>
   {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };
}

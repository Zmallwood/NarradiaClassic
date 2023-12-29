#pragma once

#include "core_v.h"

namespace Narradia
{
   class MainMenuPgV : public IPageV, public S<MainMenuPgV>
   {
     public:
      MainMenuPgV();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
   };
}

#pragma once

#include "core_v.h"

namespace Narradia
{
   class IntroPgV : public IPageV, public S<IntroPgV>
   {
     public:
      IntroPgV();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
      RenderID rid_text;
   };
}

#pragma once

namespace Narradia
{
   class FPSCounterAddV : public S<FPSCounterAddV> {
     public:
      FPSCounterAddV();
      void Render();

     private:
      RenderID rid_text;
   };
}

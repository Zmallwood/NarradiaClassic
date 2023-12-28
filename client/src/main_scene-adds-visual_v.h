#pragma once

namespace Narradia
{
   class FPSCounterModuleV : public S<FPSCounterModuleV>
   {
     public:
      FPSCounterModuleV();
      void Render();

     private:
      RenderID rid_text;
   };
}

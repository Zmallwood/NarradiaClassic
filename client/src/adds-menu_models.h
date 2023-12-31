#pragma once

namespace Narradia
{
   // Model
#if 1
   class MenuModelsAdd : public S<MenuModelsAdd> {
     public:
      void UpdateGameLogic();

     private:
      float used_fov_ = 90.0f;
   };
#endif

   // View
#if 1
   class MenuModelsAddV : public S<MenuModelsAddV> {
     public:
      void Render();
   };
#endif
}

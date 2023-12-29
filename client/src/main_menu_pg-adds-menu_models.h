#pragma once

namespace Narradia
{
   class MenuModelsAdd : public S<MenuModelsAdd>
   {
     public:
      void UpdateGameLogic();

     private:
      float used_fov_ = 90.0f;
   };
}

#pragma once

namespace Narradia
{
   class ModelDisplayAdd : public S<ModelDisplayAdd>
   {
     public:
      void UpdateGameLogic();

     private:
      float used_fov_ = 90.0f;
   };
}

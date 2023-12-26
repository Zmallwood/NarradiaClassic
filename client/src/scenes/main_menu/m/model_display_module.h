#pragma once
namespace Narradia
{
   class ModelDisplayModule : public Singleton<ModelDisplayModule>
   {
     public:
      void UpdateGameLogic();

     private:
      float used_fov_ = 90.0f;
   };
}

#pragma once
namespace Narradia
{
   class FPSCapper : public Singleton<FPSCapper>
   {
     public:
      auto RunningBelow60FPS() -> bool;

     private:
      int prev_ticks_ = 0;
   };
}

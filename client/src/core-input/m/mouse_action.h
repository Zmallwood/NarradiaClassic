#pragma once
namespace Narradia
{
   class MouseAction
   {
     public:
      std::function<void()> action;
      int z_order = 0;
   };
}

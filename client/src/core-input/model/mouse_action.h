#pragma once
#include <functional>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief An entry for storing an action for possible execution by the mouse click/release
   /// events in the MouseActionMngr.
   ////////////////////////////////////////////////////////////////////////////////
   class MouseAction {
     public:
      std::function<void()> action;
      int z_order = 0;
   };
}

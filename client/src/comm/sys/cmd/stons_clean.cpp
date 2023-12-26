#include "stons_clean.h"

namespace Narradia
{
   static std::vector<std::function<void()>> gDisposeActions;

   void AddStonDisposeAction(std::function<void()> action)
   {
      gDisposeActions.push_back(action);
   }

   void DisposeAllStons()
   {
      for (auto &action : gDisposeActions)
         action();
   }
}

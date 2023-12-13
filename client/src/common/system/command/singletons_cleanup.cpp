#include "singletons_cleanup.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Holds all dispose functions which all of them will be executed on game exit.
   ////////////////////////////////////////////////////////////////////////////////
   static std::vector<std::function<void()>> gDisposeActions;

   auto AddSingletonDisposeAction(std::function<void()> action) -> void {
      gDisposeActions.push_back(action);
   }

   auto DisposeAllSingletons() -> void {
      for (auto &action : gDisposeActions)
         action();
   }
}

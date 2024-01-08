#include "SingletonsDisposal.h"

namespace Narradia {
   static Vector<Function<void()>> g_DisposeActions;

   void AddSingletonDisposeAction(Function<void()> _action) {
      g_DisposeActions.push_back(_action);
   }
   void DisposeSingletons() {
      for (auto &_action : g_DisposeActions)
         _action();
   }
}

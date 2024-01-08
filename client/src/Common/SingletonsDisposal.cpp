#include "SingletonsDisposal.h"

namespace Narradia {
   static Vec<Function<void()>> g_disposeActions;

   void AddSingletonDisposeAction(Function<void()> _action) {
      g_disposeActions.push_back(_action);
   }
   void DisposeSingletons() {
      for (auto &_action : g_disposeActions)
         _action();
   }
}

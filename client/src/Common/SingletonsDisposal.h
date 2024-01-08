#pragma once

namespace Narradia {
   void AddSingletonDisposeAction(Function<void()> _action);
   void DisposeSingletons();
}

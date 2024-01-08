#include "Singletons_Disposal.h"

namespace Narradia {

    static Vector<Function<void()>> gDisposeActions;

    void AddSingletonDisposeAction(Function<void()> action) {

        gDisposeActions.push_back(action);
    }

    void DisposeSingletons() {

        for (auto &action : gDisposeActions)
            action();
    }
}

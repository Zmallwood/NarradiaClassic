#pragma once

namespace Narradia {

    void AddSingletonDisposeAction(Function<void()> action);
    void DisposeSingletons();
}

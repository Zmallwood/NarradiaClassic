#pragma once

namespace Narradia {
    void AddSingletonDisposeAction(std::function<void()> action);
    void DisposeAllSingletons();
}

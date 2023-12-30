#pragma once
#include <functional>
namespace Narradia
{
    void AddSingletonDisposeAction(std::function<void()> action);
    void DisposeAllSingletons();
}

#pragma once

namespace Narradia
{
   void AddStonDisposeAction(std::function<void()> action);
   void DisposeAllStons();
}

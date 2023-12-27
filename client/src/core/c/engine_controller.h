#pragma once

namespace Narradia
{
   class EngineController : public Singleton<EngineController>
   {
     public:
      auto HandleInput() -> void;
      auto UpdateGameFlow() -> void;
   };
}

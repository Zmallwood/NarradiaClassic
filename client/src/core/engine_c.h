#pragma once

namespace Narradia
{
   class EngineC : public S<EngineC>
   {
     public:
      auto HandleInput() -> void;
      auto UpdateGameFlow() -> void;
   };
}

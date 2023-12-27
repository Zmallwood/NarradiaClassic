#pragma once

namespace Narradia
{
   class ISceneController
   {
     public:
      virtual auto OnEnter() -> void = 0;
      auto UpdateGameFlow() -> void;

     protected:
      virtual void UpdateGameFlowDerived() = 0;
   };
}

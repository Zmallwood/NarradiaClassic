#pragma once

namespace Narradia
{
   class EngineView : public Singleton<EngineView>
   {
     public:
      auto Render() -> void;
   };
}

#pragma once
#include "cmd/poll_events.h"
#include "scene_mngr_controller.h"
namespace Narradia
{
   class EngineController : public Singleton<EngineController>
   {
     public:
      auto HandleInput() -> void;
      auto UpdateGameFlow() -> void;
   };
}

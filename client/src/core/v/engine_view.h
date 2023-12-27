#pragma once

#include "console_view.h"
#include "cursor_view.h"
#include "graphics_view.h"
#include "scene_mngr_view.h"

namespace Narradia
{
   class EngineView : public Singleton<EngineView>
   {
     public:
      auto Render() -> void;
   };
}

#pragma once

#include "core/m/engine.h"
#include "core/m/graphics.h"
#include "graphics_gl_view.h"

namespace Narradia
{
   class GraphicsView : public Singleton<GraphicsView>
   {
     public:
      GraphicsView();

      auto ClearCanvas() -> void;

      auto PresentCanvas() -> void;
   };
}

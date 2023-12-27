#pragma once

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

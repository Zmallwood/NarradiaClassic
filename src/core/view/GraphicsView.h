#pragma once

namespace Narradia {
    /**
     View for Graphics.
    */
    class GraphicsView : public Singleton<GraphicsView> {
      public:
        GraphicsView();
        void ClearCanvas();
        void PresentCanvas();
    };
}

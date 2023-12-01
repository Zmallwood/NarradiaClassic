#pragma once

namespace Narradia {

    class GraphicsGLView : public Singleton<GraphicsGLView> {
      public:
        GraphicsGLView();

      private:
        static constexpr bool kCullFace = false;
        const Color kClearColor = {0, 150, 255, 0};
    };
}

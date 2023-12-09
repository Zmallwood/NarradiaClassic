#pragma once

namespace Narradia
{
    /**
    Holds and initializes OpenGL-specific configurations.
    */
    class GraphicsGLView : public Singleton<GraphicsGLView> {
      public:
        GraphicsGLView();

      private:
        static constexpr bool kCullFace = false;
        const Color kClearColor = {0.0f, 0.0f, 0.0f, 1.0f};
    };
}

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
        const Color kClearColor = {1.0f, 0.8f, 0.3f, 1.0f};
    };
}

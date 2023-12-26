#pragma once
namespace Narradia
{
   class GraphicsGLView : public Singleton<GraphicsGLView>
   {
     public:
      GraphicsGLView();

     private:
      static constexpr bool kCullFace = false;
      const Color kClearColor = Colors::mild_blue;
   };
}

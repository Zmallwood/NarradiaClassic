#pragma once

namespace Narradia
{
   class GraphicsGLV : public S<GraphicsGLV>
   {
     public:
      GraphicsGLV();

     private:
      static constexpr bool kCullFace = false;
      const Color kClearColor = Colors::mild_blue;
   };
}

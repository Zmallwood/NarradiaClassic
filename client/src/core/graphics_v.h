#pragma once

namespace Narradia
{
   class GraphicsV : public S<GraphicsV>
   {
     public:
      GraphicsV();
      void ClearCanvas();
      void PresentCanvas();
   };
}

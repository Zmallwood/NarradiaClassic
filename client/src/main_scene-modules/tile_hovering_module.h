#pragma once

namespace Narradia
{
   class TileHoveringModule : public S<TileHoveringModule>
   {
     public:
      void UpdateGameLogic();
      auto hovered_tile()
      {
         return hovered_tile_;
      }

     private:
      Point hovered_tile_ = {-1, -1};
   };
}

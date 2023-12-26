#pragma once
namespace Narradia
{
   class TileHoveringModule : public Singleton<TileHoveringModule>
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

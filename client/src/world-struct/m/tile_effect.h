#pragma once
namespace Narradia
{
   /**
    Describes a effect being present on a tile, such as
    initiated from a player skill.
   */
   class TileEffect
   {
     public:
      std::string_view type;
      int ticks_started = 0;
   };
}

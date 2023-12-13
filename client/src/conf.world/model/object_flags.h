#pragma once
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Flags that can be set for object types to modify their behaviour.
   ////////////////////////////////////////////////////////////////////////////////
   namespace ObjectFlags
   {
      static constexpr int None = 0;
      static constexpr int NoObstacle = 1 << 0;
   };
}

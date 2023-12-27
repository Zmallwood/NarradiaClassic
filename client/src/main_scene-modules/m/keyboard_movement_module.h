#pragma once

namespace Narradia
{
   class KeyboardMovementModule : public Singleton<KeyboardMovementModule>
   {
     public:
      void UpdateGameLogic();
   };
}

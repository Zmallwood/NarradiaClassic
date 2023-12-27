#pragma once

namespace Narradia
{
   class CombatChaseMovementModule : public Singleton<CombatChaseMovementModule>
   {
     public:
      void UpdateGameLogic();
   };
}

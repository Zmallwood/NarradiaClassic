#pragma once

namespace Narradia {
  class SkillPerformingModule : public Singleton<SkillPerformingModule> {
   public:
    void UpdateGameLogic();

   private:
    int ticks_last_skill_tick_ = 0;
    float skill_ticks_frequency_ = 0.4f;
  };
}

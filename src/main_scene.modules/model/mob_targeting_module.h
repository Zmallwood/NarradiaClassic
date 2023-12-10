#pragma once
namespace Narradia {
  class Mob;

  class MobTargetingModule : public Singleton<MobTargetingModule> {
   public:
    void UpdateGameLogic();
    void ClearTarget();

    auto targeted_mob() {
      return targeted_mob_;
    }

   private:
    std::shared_ptr<Mob> targeted_mob_;
  };
}

#pragma once

namespace Narradia {
  class FPSCounterModule : public Singleton<FPSCounterModule> {
   public:
    void UpdateGameLogic();

    auto fps() {
      return fps_;
    }

   private:
    int fps_ = 0;
    int frames_count_ = 0;
    int ticks_last_update_ = 0;

    static constexpr int kMillisPerSecond = 1000;
  };
}

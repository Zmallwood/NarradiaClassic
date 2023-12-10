#pragma once

namespace Narradia {
  /**
   Model for Engine.
  */
  class Engine : public Singleton<Engine> {
   public:
    Engine();
    void UpdateGameLogic();

    auto is_running() {
      return is_running_;
    }
    void set_running(bool value) {
      is_running_ = value;
    }

    auto title() {
      return title_;
    }

   private:
    bool is_running_ = true;
    std::string_view title_ = "Narradia";
  };
}

#pragma once

namespace Narradia
{
    /**
     * Model for Engine.
     */
    class Engine : public Singleton<Engine> {
      public:
        Engine();
        void UpdateGameLogic();

        bool is_running() { return is_running_; }
        void set_running(bool value) { is_running_ = value; }

        std::string_view title() { return title_; }

      private:
        bool is_running_ = true;
        std::string_view title_ = "Narradia";
    };
}

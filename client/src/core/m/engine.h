#pragma once
#include "core-input/m/mouse_input.h"
#include "cursor.h"
#include "scene_mngr.h"
namespace Narradia
{
   class Engine : public Singleton<Engine>
   {
     public:
      Engine();

      void UpdateGameLogic();

      void Finalize();

      auto is_running()
      {
         return is_running_;
      }

      void set_running(bool value)
      {
         is_running_ = value;
      }

      auto title()
      {
         return title_;
      }

     private:
      bool is_running_ = true;
      std::string_view title_ = "Narradia";
   };
}

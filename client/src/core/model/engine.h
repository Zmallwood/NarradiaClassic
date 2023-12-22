#pragma once
#include "core-input/model/mouse_input.h"
#include "cursor.h"
#include "scene_mngr.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Model for Engine.
   ////////////////////////////////////////////////////////////////////////////////
   class Engine : public Singleton<Engine> {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Seeds the randomization to get unique random generations each game start.
      ////////////////////////////////////////////////////////////////////////////////
      Engine();

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Update game logic for current frame.
      ////////////////////////////////////////////////////////////////////////////////
      void UpdateGameLogic();

      void Finalize();

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

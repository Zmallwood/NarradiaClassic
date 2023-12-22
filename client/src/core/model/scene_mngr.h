#pragma once
#include "iscene.h"
#include "scene_names.h"
#include "scenes/intro/model/intro_scene.h"
#include "scenes/main/model/main_scene.h"
#include "scenes/main_menu/model/main_menu_scene.h"
#include "scenes/map_overview_gen/model/map_overview_gen_scene.h"
#include <map>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Model for SceneMngr.
   ////////////////////////////////////////////////////////////////////////////////
   class SceneMngr : public Singleton<SceneMngr> {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Initialize scenes that will be used.
      ////////////////////////////////////////////////////////////////////////////////
      SceneMngr();

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Update game logic for currently displayed scene.
      ////////////////////////////////////////////////////////////////////////////////
      void UpdateGameLogicCurrScene();

      void FinalizeCurrScene();

      auto curr_scene() {
         return curr_scene_;
      }

      void set_curr_scene(SceneNames value) {
         curr_scene_ = value;
      }

      auto curr_scene_canceled() {
         return curr_scene_canceled_;
      }

      void set_curr_scene_canceled(bool value) {
         curr_scene_canceled_ = value;
      }

     private:
      std::map<SceneNames, std::shared_ptr<IScene>> scenes_;
      SceneNames curr_scene_ = SceneNames::None;
      bool curr_scene_canceled_ = false;
   };
}

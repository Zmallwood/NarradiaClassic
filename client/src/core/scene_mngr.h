#pragma once

#include "scene_names.h"

namespace Narradia
{
   class IScene;

   class SceneMngr : public S<SceneMngr>
   {
     public:
      SceneMngr();
      void UpdateGameLogicCurrScene();
      void FinalizeCurrScene();
      auto curr_scene()
      {
         return curr_scene_;
      }
      void set_curr_scene(SceneNames value)
      {
         curr_scene_ = value;
      }
      auto curr_scene_canceled()
      {
         return curr_scene_canceled_;
      }
      void set_curr_scene_canceled(bool value)
      {
         curr_scene_canceled_ = value;
      }

     private:
      std::map<SceneNames, std::shared_ptr<IScene>> scenes_;
      SceneNames curr_scene_ = SceneNames::None;
      bool curr_scene_canceled_ = false;
   };
}

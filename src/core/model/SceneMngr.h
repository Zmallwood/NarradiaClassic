#pragma once
#include "IScene.h"
#include "SceneNames.h"

namespace Narradia
{
    /**
     * Model for SceneMngr.
     */
    class SceneMngr : public Singleton<SceneMngr> {
      public:
        SceneMngr();
        void UpdateGameLogicCurrScene();

        SceneNames curr_scene() { return curr_scene_; }
        void set_curr_scene(SceneNames value) { curr_scene_ = value; }

      private:
        std::map<SceneNames, std::shared_ptr<IScene>> scenes_;
        SceneNames curr_scene_ = SceneNames::None;
    };
}

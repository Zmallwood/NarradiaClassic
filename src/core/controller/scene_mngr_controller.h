#pragma once
#include "core/model/scene_names.h"
#include "iscene_controller.h"
namespace Narradia {
  /**
   Controller for SceneMngr.
  */
  class SceneMngrController : public Singleton<SceneMngrController> {
   public:
    SceneMngrController();
    void UpdateGameFlowCurrScene();
    void ChangeScene(SceneNames new_scene);

   private:
    std::map<SceneNames, std::shared_ptr<ISceneController>> scene_controllers_;
  };
}

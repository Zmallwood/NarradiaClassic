#pragma once

#include "core.h"

namespace Narradia
{
   class EngineC : public S<EngineC>
   {
     public:
      auto HandleInput() -> void;
      auto UpdateGameFlow() -> void;

     private:
      void PollEvents();
   };

   class ISceneC;

   class SceneMngrC : public S<SceneMngrC>
   {
     public:
      SceneMngrC();
      auto UpdateGameFlowCurrScene() -> void;
      auto ChangeScene(SceneNames new_scene) -> void;

     private:
      std::map<SceneNames, std::shared_ptr<ISceneC>> scene_controllers_;
   };

   class ISceneC
   {
     public:
      virtual auto OnEnter() -> void = 0;
      auto UpdateGameFlow() -> void;

     protected:
      virtual void UpdateGameFlowDerived() = 0;
   };
}

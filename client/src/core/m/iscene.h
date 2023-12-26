#pragma once
#include "core-gui/m/scene_gui.h"
namespace Narradia
{
   class IScene
   {
     public:
      IScene()
          : scene_gui_(std::make_shared<SceneGui>())
      {
      }

      void UpdateGameLogic();
      virtual void Finalize() = 0;

      auto scene_gui()
      {
         return scene_gui_;
      }

     protected:
      virtual void UpdateGameLogicDerived() = 0;

      std::shared_ptr<SceneGui> scene_gui_;
   };
}

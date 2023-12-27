#pragma once

namespace Narradia
{
   class SceneGui;

   class IScene
   {
     public:
      IScene();
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

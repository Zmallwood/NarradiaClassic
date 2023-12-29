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

   class IPageC;

   class PageMngrC : public S<PageMngrC>
   {
     public:
      PageMngrC();
      auto UpdateGameFlowCurrScene() -> void;
      auto ChangeScene(PageNames new_scene) -> void;

     private:
      std::map<PageNames, std::shared_ptr<IPageC>> scene_controllers_;
   };

   class IPageC
   {
     public:
      virtual auto OnEnter() -> void = 0;
      auto UpdateGameFlow() -> void;

     protected:
      virtual void UpdateGameFlowDerived() = 0;
   };
}

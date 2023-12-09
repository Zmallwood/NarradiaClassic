#pragma once
#include "core.gui/model/SceneGui.h"

namespace Narradia {
    /**
     Model for IScene.
    */
    class IScene {
      public:
        IScene()
            : scene_gui_(std::make_shared<SceneGui>()) {}

        void UpdateGameLogic();

        std::shared_ptr<SceneGui> scene_gui() { return scene_gui_; }

      protected:
        virtual void UpdateGameLogicDerived() = 0;

        std::shared_ptr<SceneGui> scene_gui_;
    };
}

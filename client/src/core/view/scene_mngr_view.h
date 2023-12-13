#pragma once
#include "../model/scene_mngr.h"
#include "../model/scene_names.h"
#include "iscene_view.h"
#include "../../scenes/intro/view/intro_scene_view.h"
#include "../../scenes/main/view/main_scene_view.h"
#include "../../scenes/main_menu/view/main_menu_scene_view.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief View for SceneMngr.
   ////////////////////////////////////////////////////////////////////////////////
   class SceneMngrView : public Singleton<SceneMngrView> {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Initialize scene views that will be used.
      ////////////////////////////////////////////////////////////////////////////////
      SceneMngrView();

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Render currently displayed scene.
      ////////////////////////////////////////////////////////////////////////////////
      auto RenderCurrScene() -> void;

     private:
      std::map<SceneNames, std::shared_ptr<ISceneView>> scene_views_;
   };
}

#include "Pages.h"
#include "Adds.h"
#include "Core/Assets/nModelBank.h"
#include "Core/Core.h"
#include "Core/Rendering/GroundRendering.h"
#include "Core/GuiCore/nSceneGui.h"
#include "Core/GuiCore/nGuiButton.h"
#include "Core/GuiCore/nSceneGuiView.h"
#include "Core/GuiCore/nGuiButtonView.h"
#include "Core/Rendering/ImagesRendering.h"
#include "Core/Rendering/ModelsRendering.h"
#include "Core/Rendering/TextRendering.h"
#include "GuiMainPg.h"
#include "MapGenAdd.h"
#include "WorldAdd.h"
#include "WorldStructure/Actors/Player.h"
#include "WorldStructure/WorldStructure.h"

namespace Narradia {

   // Model

#if 1
   // IntroPg
#if 1
   void IntroPg::UpdateGameLogicDerived() {
   }
#endif

   // MainMenuPg
#if 1
   MainMenuPg::MainMenuPg() {
      scene_gui()->AddGuiComponent(
          MakeShared<nGuiButton>("Play", RectF{0.05f, 0.4f, 0.2f, 0.1f}, [] {
             PageMngrC::get()->ChangeScene(PageNames::MapCreation);
          }));

      scene_gui()->AddGuiComponent(MakeShared<nGuiButton>(
          "Exit", RectF{0.05f, 0.55f, 0.2f, 0.1f}, [] { Engine::get()->set_running(false); }));
   }

   void MainMenuPg::UpdateGameLogicDerived() {
      MenuModelsAdd::get()->UpdateGameLogic();
   }
#endif

   // MapCreationPg
#if 1
   void MapCreationPg::UpdateGameLogicDerived() {
      WorldAdd::get()->UpdateGameLogic();
   }

   void MapCreationPg::Finalize() {
      PageMngrC::get()->ChangeScene(PageNames::Main);
   }
#endif

   // MainPg
#if 1
   MainPg::MainPg() {
      scene_gui()->AddGuiComponent(MakeShared<ExperienceBar>());
      scene_gui()->AddGuiComponent(MakeShared<StatusPanel>());
      scene_gui()->AddGuiComponent(GuiWindowWorldMap::get());
   }

   void MainPg::UpdateGameLogicDerived() {
      try {
         KbBindingsAdd::get()->UpdateGameLogic();
         KeyboardMovementAdd::get()->UpdateGameLogic();
         MouseMovementAdd::get()->UpdateGameLogic();
         WorldAdd::get()->UpdateGameLogic();
         MouseRotationAdd::get()->UpdateGameLogic();
         TileHoveringAdd::get()->UpdateGameLogic();
         SkillPerformingAdd::get()->UpdateGameLogic();
         FPSCounterAdd::get()->UpdateGameLogic();
      } catch (Exception &e) {
         Console::get()->Print("Exception in MainPg::UpdateGameLogicDerived: " + String(e.what()));
      }
   }
#endif
#endif

   // View

#if 1
   // IntroPgV
#if 1
   IntroPgView ::IntroPgView () {
      scene_gui_view_->SetSceneGui(IntroPg::get()->scene_gui());

      rid_background = NewImage();
      rid_logo = NewImage();
      rid_text = NewString();
   }

   void IntroPgView ::RenderDerived() {
      RectF dest_background = {0.0f, 0.0f, 1.0f, 1.0f};

      DrawImage("DefaultSceneBackground", rid_background, dest_background);
      DrawImage("NarradiaLogo", rid_logo, {0.3f, 0.1f, 0.4f, 0.2f});

      RectF rect = {0.1f, 0.1f, 0.2f, 0.1f};
      Color color = {1.0f, 0.0f, 0.0f, 255};

      if (SDL_GetTicks() % 600 > 300)
         DrawString(rid_text, "Press to start", {0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, true);
   }
#endif

   // MainMenuPgV
#if 1
   MainMenuPgView::MainMenuPgView() {
      scene_gui_view_->SetSceneGui(MainMenuPg::get()->scene_gui());
      scene_gui_view_->AddGuiComponentView(MakeShared<nGuiButtonView>());
      scene_gui_view_->AddGuiComponentView(MakeShared<nGuiButtonView>());

      rid_background = NewImage();
      rid_logo = NewImage();
   }

   void MainMenuPgView::RenderDerived() {
      DrawImage("MainMenuSceneBackground", rid_background, {0.0f, 0.0f, 1.0f, 1.0f});
      DrawImage("NarradiaLogo", rid_logo, {0.05f, 0.1f, 0.2f, 0.1f});

      MenuModelsAddView::get()->Render();
   }
#endif

   // MapCreationPgV
#if 1
   void MapCreationPgView::RenderDerived() {
      MapGenAddView::get()->Render();
   }
#endif

   // MainPgV
#if 1
   MainPgView::MainPgView() {
      scene_gui_view_->SetSceneGui(MainPg::get()->scene_gui());
      scene_gui_view_->AddGuiComponentView(MakeShared<ExperienceBarV>());
      scene_gui_view_->AddGuiComponentView(MakeShared<StatusPanelV>());
      scene_gui_view_->AddGuiComponentView(MakeShared<GuiWindowWorldMapV>());
   }

   void MainPgView::RenderDerived() {
      WorldAddView::get()->Render();
      FPSCounterAddView::get()->Render();
   }
#endif

#endif

   // Controller

#if 1
   // IntroPgC
#if 1
   void IntroPgC::OnEnter() {
   }

   void IntroPgC::UpdateGameFlowDerived() {
      if (KbInput::get()->AnyKeyIsPressedPickResult()) {
         PageMngrC::get()->ChangeScene(PageNames::MainMenu);
      }

      MouseInput::get()->left_btn()->AddFiredAction(
          [] { PageMngrC::get()->ChangeScene(PageNames::MainMenu); });

      MouseInput::get()->right_btn()->AddFiredAction(
          [] { PageMngrC::get()->ChangeScene(PageNames::MainMenu); });
   }
#endif

   // MainMenuPgC
#if 1
   void MainMenuPgC::OnEnter() {
      auto all_models = *nModelBank::get()->Models();

      for (auto &entry : all_models)
         NewModel(entry.first);
   }

   void MainMenuPgC::UpdateGameFlowDerived() {
   }
#endif

   // MapCreationPgC
#if 1
   void MapCreationPgC::OnEnter() {
      auto map_area = World::get()->CurrWorldArea();
      auto x = map_area->Width() / 2.0f;
      auto y = map_area->Height() / 2.0f;

      Player::get()->set_pos({x, 0.0f, y});
   }

   void MapCreationPgC::UpdateGameFlowDerived() {
   }
#endif

   // MainPgC
#if 1
   void MainPgC::OnEnter() {
      Console::get()->Print("Entering Narradia");
      PlayerSpawnPositioningAdd::get()->SpawnAtGoodLocation();
   }

   void MainPgC::UpdateGameFlowDerived() {
   }
#endif
#endif

}

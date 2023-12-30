#if 1
#include "core_v.h"
#include "pages_v.h"
#include "render-text/cmd_v/draw_string.h"
#include "render-text/cmd_v/new_string.h"
#include "render/renderer_2d_images_v.h"
#endif

namespace Narradia
{
// EngineV
#if 1
   void EngineV::Render() {
      try {
         GraphicsV::get()->ClearCanvas();
         PageMngrV::get()->RenderCurrScene();
         ConsoleV::get()->Render();
         CursorV::get()->RenderCursor();
         GraphicsV::get()->PresentCanvas();
      }
      catch (std::exception &e) {
         Console::get()->Print("Exception in EngineV::Render:" + std::string(e.what()));
      }
   };
#endif

      // PageMngrV
#if 1
   PageMngrV::PageMngrV() {
      scene_views_[PageNames::Intro] = IntroPgV::get();
      scene_views_[PageNames::MainMenu] = MainMenuPgV::get();
      scene_views_[PageNames::MapCreation] = MapCreationPgV::get();
      scene_views_[PageNames::Main] = MainPgV::get();
   }
   auto PageMngrV::RenderCurrScene() -> void {
      if (PageMngr::get()->curr_scene_canceled())
         return;
      auto curr_scene = PageMngr::get()->curr_scene();
      if (scene_views_.count(curr_scene) != 0)
         scene_views_.at(curr_scene)->Render();
   }
#endif

   // IPageV
#if 1
   IPageV::IPageV()
       : scene_gui_view_(std::make_shared<SceneGuiV>()) {
   }
   void IPageV::Render() {
      RenderDerived();
      scene_gui_view_->Render();
   }
#endif

// CursorV
#if 1
   CursorV::CursorV() {
      SDL_ShowCursor(0);
      rid_image = NewImage();
   }
   void CursorV::RenderCursor() {
      auto mouse_pos = MousePosition();
      auto w = kCursorWidth;
      auto h = w * AspectRatio();
      RectF rect = {mouse_pos.x - w, mouse_pos.y - h, w * 2, h * 2};
      auto image_name = Cursor::get()->GetCursorImageName();
      DrawImage(image_name, rid_image, rect);
   }
#endif

   // GraphicsV
#if 1
   GraphicsV::GraphicsV() {
      auto win_size = Graphics::get()->win_size();
      auto win_flags = Graphics::get()->win_flags();
      auto win = std::shared_ptr<SDL_Window>(
          SDL_CreateWindow(Engine::get()->title().data(), 0, 0, win_size.w, win_size.h, win_flags),
          SDLDeleter());
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
      if (SDL_GL_CreateContext(win.get()) == nullptr) {
         std::cout << "OpenGL context could not be "
                      "created! SDL Error: "
                   << std::string(SDL_GetError()) << std::endl;
         return;
      }
      Graphics::get()->set_win(win);
      InitGL();
   }
   void GraphicsV::ClearCanvas() {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   }
   void GraphicsV::PresentCanvas() {
      SDL_GL_SwapWindow(Graphics::get()->win().get());
   }
   void GraphicsV::InitGL() {
      glewExperimental = GL_TRUE;
      auto glew_error = glewInit();
      if (glew_error != GLEW_OK)
         std::cout << "Error initializing GLEW: " << glewGetErrorString(glew_error) << std::endl;
      if (SDL_GL_SetSwapInterval(0) < 0)
         std::cout << "Warning: Unable to disable VSync, SDL Error: " << SDL_GetError()
                   << std::endl;
      glClearColor(kClearColor.r, kClearColor.g, kClearColor.b, kClearColor.a);
      if (kCullFace) {
         glEnable(GL_CULL_FACE);
         glCullFace(GL_FRONT);
      }
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   }
#endif

   // ConsoleV
#if 1
   ConsoleV::ConsoleV() {
      rid_image_ = NewImage();
      rid_split_line_ = NewImage();
      rid_cmd_line_input_arrow_ = NewImage();
      rid_input_text_ = NewString();
      for (auto i = 0; i < ConsoleCalc::get()->MaxNumLines(); i++)
         rids_text_lines_.push_back(NewString());
   }
   void ConsoleV::Render() const {
      auto model = Console::get();
      if (!model->enabled())
         return;

      DrawImage("TextOutBoxBack", rid_image_, Console::get()->Bounds());

      for (auto i = 0; i < ConsoleCalc::get()->MaxNumLines(); i++) {
         auto text_line_index = ConsoleCalc::get()->TextLineIndex(i);
         if (text_line_index >= 0) {
            PointF position = ConsoleCalc::get()->TextLinePosition(i);
            DrawString(
                rids_text_lines_.at(i), model->text_lines().at(text_line_index).text, position,
                model->text_lines().at(text_line_index).color);
         }
      }

      DrawImage("Wheat", rid_split_line_, ConsoleCalc::get()->HorizontalSplitterRect());
      if (!model->input_active())
         return;

      DrawImage(
          "CommandLineInputArrow", rid_cmd_line_input_arrow_, ConsoleCalc::get()->InputArrowRect());

      DrawString(
          rid_input_text_, model->InputTextWithCursor(), ConsoleCalc::get()->InputTextPosition());
   }
#endif
}

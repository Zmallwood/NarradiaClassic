#pragma once

#include "core.h"
#include "gui-core_v.h"

namespace Narradia
{
   class EngineV : public S<EngineV>
   {
     public:
      void Render();
   };

   class ISceneV;

   class SceneMngrV : public S<SceneMngrV>
   {
     public:
      SceneMngrV();
      void RenderCurrScene();

     private:
      std::map<SceneNames, std::shared_ptr<ISceneV>> scene_views_;
   };

   class ISceneV
   {
     public:
      ISceneV();
      void Render();

     protected:
      virtual void RenderDerived() = 0;

      std::shared_ptr<SceneGuiV> scene_gui_view_;
   };

   class CursorV : public S<CursorV>
   {
     public:
      CursorV();
      void RenderCursor();

     private:
      RenderID rid_image;

      static constexpr float kCursorWidth = 0.02f;
   };

   class GraphicsV : public S<GraphicsV>
   {
     public:
      GraphicsV();
      void ClearCanvas();
      void PresentCanvas();

     private:
      void InitGL();

      static constexpr bool kCullFace = false;
      const Color kClearColor = Colors::mild_blue;
   };
}

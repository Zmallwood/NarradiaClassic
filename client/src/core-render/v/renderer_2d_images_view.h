#pragma once
#include "../../core-render-shaders/m/2d_images_fragment.inc.cpp"
#include "../../core-render-shaders/m/2d_images_vertex.inc.cpp"
#include "renderer_base_view.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Prepares and renders 2D images to the canvas.
   ////////////////////////////////////////////////////////////////////////////////
   class Renderer2DImagesView : public RendererBaseView, public Singleton<Renderer2DImagesView>
   {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Creates the shader program for the provided shader sources.
      ////////////////////////////////////////////////////////////////////////////////
      Renderer2DImagesView();

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Forwarding cleanup command to renderer base view.
      ////////////////////////////////////////////////////////////////////////////////
      ~Renderer2DImagesView();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
   };
}

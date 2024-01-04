#if 1
#include "drw_colors.h"
#include "conf.h"
#endif

namespace Narradia
{
// View
#if 1
   // DrwSolidColorsV
#if 1
   DrwColorsV::DrwColorsV() {

      shader_program_view()->Create(
          vertex_shader_source_2d_solid_colors, fragment_shader_source_2d_solid_colors);
   }

   DrwColorsV::~DrwColorsV() {

      if (kVerbose)
         std::cout << "Cleaning up DrwSolidColorsV.\n";

      CleanupBase();

      if (kVerbose)
         std::cout << "Cleaning up of DrwSolidColorsV finished.\n";
   }
#endif

   // Free functions
#if 1
   auto NewRect() -> RenderID {

      auto renderer = DrwColorsV::get();
      auto renderer_base = renderer->renderer_base();
      auto vao_id = renderer_base->GenNewVAOId();
      renderer->UseVAOBegin(vao_id);
      auto index_buffer_id = renderer_base->GenNewBufId(BufferTypes::Indices, vao_id);
      auto position_buffer_id = renderer_base->GenNewBufId(BufferTypes::Positions2D, vao_id);
      auto color_buffer_id = renderer_base->GenNewBufId(BufferTypes::Colors, vao_id);
      renderer->SetIndicesData(index_buffer_id, RendBase::kNumVerticesInRectangle, nullptr);
      renderer->SetData(
          position_buffer_id, RendBase::kNumVerticesInRectangle, nullptr, BufferTypes::Positions2D);
      renderer->SetData(
          color_buffer_id, RendBase::kNumVerticesInRectangle, nullptr, BufferTypes::Colors);
      renderer->UseVAOEnd();

      return vao_id;
   }

   auto DrawRect(RenderID vao_id, RectF rect, Color color) -> void {

      auto renderer = DrwColorsV::get();
      auto renderer_base = renderer->renderer_base();
      auto gl_rect = rect.ToGLRectF();
      Vertex2F vertices[RendBase::kNumVerticesInRectangle];
      vertices[0].pos = {gl_rect.x, gl_rect.y - gl_rect.h};
      vertices[1].pos = {gl_rect.x, gl_rect.y};
      vertices[2].pos = {gl_rect.x + gl_rect.w, gl_rect.y};
      vertices[3].pos = {gl_rect.x + gl_rect.w, gl_rect.y - gl_rect.h};
      glDisable(GL_DEPTH_TEST);
      auto indices = std::vector<int>(RendBase::kNumVerticesInRectangle);
      std::iota(std::begin(indices), std::end(indices), 0);
      std::vector<float> positions;
      std::vector<float> colors;

      for (auto &vertex : vertices) {
         positions.push_back(vertex.pos.x);
         positions.push_back(vertex.pos.y);
         colors.push_back(color.r);
         colors.push_back(color.g);
         colors.push_back(color.b);
         colors.push_back(color.a);
      }

      renderer->UseVAOBegin(vao_id);
      auto index_buffer_id = renderer_base->BufId(BufferTypes::Indices, vao_id);
      auto position_buffer_id = renderer_base->BufId(BufferTypes::Positions2D, vao_id);
      auto color_buffer_id = renderer_base->BufId(BufferTypes::Colors, vao_id);
      renderer->UpdateIndicesData(index_buffer_id, indices);
      renderer->UpdateData(
          position_buffer_id, positions, BufferTypes::Positions2D,
          DrwColorsV::kLocationPosition);
      renderer->UpdateData(
          color_buffer_id, colors, BufferTypes::Colors, DrwColorsV::kLocationColor);
      glDrawElements(GL_LINE_STRIP, RendBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
      renderer->UseVAOEnd();
   }

   auto FillRect(RenderID vao_id, RectF rect, Color color) -> void {

      auto renderer = DrwColorsV::get();
      auto renderer_base = renderer->renderer_base();
      auto gl_rect = rect.ToGLRectF();
      Vertex2F vertices[RendBase::kNumVerticesInRectangle];
      vertices[0].pos = {gl_rect.x, gl_rect.y - gl_rect.h};
      vertices[1].pos = {gl_rect.x, gl_rect.y};
      vertices[2].pos = {gl_rect.x + gl_rect.w, gl_rect.y};
      vertices[3].pos = {gl_rect.x + gl_rect.w, gl_rect.y - gl_rect.h};
      glDisable(GL_DEPTH_TEST);
      auto indices = std::vector<int>(RendBase::kNumVerticesInRectangle);
      std::iota(std::begin(indices), std::end(indices), 0);
      std::vector<float> positions;
      std::vector<float> colors;

      for (auto &vertex : vertices) {
         positions.push_back(vertex.pos.x);
         positions.push_back(vertex.pos.y);
         colors.push_back(color.r);
         colors.push_back(color.g);
         colors.push_back(color.b);
         colors.push_back(color.a);
      }

      renderer->UseVAOBegin(vao_id);
      auto index_buffer_id = renderer_base->BufId(BufferTypes::Indices, vao_id);
      auto position_buffer_id = renderer_base->BufId(BufferTypes::Positions2D, vao_id);
      auto color_buffer_id = renderer_base->BufId(BufferTypes::Colors, vao_id);
      renderer->UpdateIndicesData(index_buffer_id, indices);
      renderer->UpdateData(
          position_buffer_id, positions, BufferTypes::Positions2D,
          DrwColorsV::kLocationPosition);
      renderer->UpdateData(
          color_buffer_id, colors, BufferTypes::Colors, DrwColorsV::kLocationColor);
      glDrawElements(GL_TRIANGLE_FAN, RendBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
      renderer->UseVAOEnd();
   }
#endif
#endif
}

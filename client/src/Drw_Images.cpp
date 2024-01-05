#if 1
#include "Drw_Images.h"
#include "Assets.h"
#include "Conf.h"
#endif

namespace Narradia
{

   // View
#if 1
   // DrwImagesV
#if 1
   DrwImagesV::DrwImagesV() {

      shader_program_view()->Create(
          vertex_shader_source_2d_images, fragment_shader_source_2d_images);
   }

   DrwImagesV::~DrwImagesV() {

      if (kVerbose)
         std::cout << "Cleaning up DrwImagesV.\n";

      CleanupBase();

      if (kVerbose)
         std::cout << "Cleaning up of DrwImagesV finished.\n";
   }
#endif

   // Free functions
#if 1
   RenderID NewImage() {

      auto renderer = DrwImagesV::get();
      auto renderer_base = renderer->renderer_base();
      auto vao_id = renderer_base->GenNewVAOId();
      renderer->UseVAOBegin(vao_id);
      auto index_buffer_id = renderer_base->GenNewBufId(BufferTypes::Indices, vao_id);
      auto position_buffer_id = renderer_base->GenNewBufId(BufferTypes::Positions2D, vao_id);
      auto color_buffer_id = renderer_base->GenNewBufId(BufferTypes::Colors, vao_id);
      auto uv_buffer_id = renderer_base->GenNewBufId(BufferTypes::Uvs, vao_id);
      renderer->SetIndicesData(index_buffer_id, RendBase::kNumVerticesInRectangle, nullptr);
      renderer->SetData(
          position_buffer_id, RendBase::kNumVerticesInRectangle, nullptr, BufferTypes::Positions2D);
      renderer->SetData(
          color_buffer_id, RendBase::kNumVerticesInRectangle, nullptr, BufferTypes::Colors);
      renderer->SetData(uv_buffer_id, RendBase::kNumVerticesInRectangle, nullptr, BufferTypes::Uvs);
      renderer->UseVAOEnd();

      return vao_id;
   }

   void DrawImage(StringView image_name, RenderID rid, const RectF &dest, Color color) {

      auto renderer = DrwImagesV::get();
      auto renderer_base = renderer->renderer_base();
      auto gl_rect = dest.ToGLRectF();
      Vertex2F vertices[RendBase::kNumVerticesInRectangle];
      vertices[0].pos = {gl_rect.x, gl_rect.y - gl_rect.h};
      vertices[1].pos = {gl_rect.x, gl_rect.y};
      vertices[2].pos = {gl_rect.x + gl_rect.w, gl_rect.y};
      vertices[3].pos = {gl_rect.x + gl_rect.w, gl_rect.y - gl_rect.h};
      vertices[0].uv = {0.0f, 1.0f};
      vertices[1].uv = {0.0f, 0.0f};
      vertices[2].uv = {1.0f, 0.0f};
      vertices[3].uv = {1.0f, 1.0f};
      glDisable(GL_DEPTH_TEST);
      auto image_id = ImageBank::get()->GetImage(image_name);
      glBindTexture(GL_TEXTURE_2D, image_id);
      auto indices = std::vector<int>(RendBase::kNumVerticesInRectangle);
      std::iota(std::begin(indices), std::end(indices), 0);
      Vec<float> positions;
      Vec<float> colors;
      Vec<float> uvs;

      for (auto &vertex : vertices) {
         positions.push_back(vertex.pos.x);
         positions.push_back(vertex.pos.y);
         colors.push_back(color.r);
         colors.push_back(color.g);
         colors.push_back(color.b);
         colors.push_back(color.a);
         uvs.push_back(vertex.uv.x);
         uvs.push_back(vertex.uv.y);
      }

      renderer->UseVAOBegin(rid);
      auto index_buffer_id = renderer_base->BufId(BufferTypes::Indices, rid);
      auto position_buffer_id = renderer_base->BufId(BufferTypes::Positions2D, rid);
      auto color_buffer_id = renderer_base->BufId(BufferTypes::Colors, rid);
      auto uv_buffer_id = renderer_base->BufId(BufferTypes::Uvs, rid);
      renderer->UpdateIndicesData(index_buffer_id, indices);
      renderer->UpdateData(
          position_buffer_id, positions, BufferTypes::Positions2D, DrwImagesV::kLocationPosition);
      renderer->UpdateData(
          color_buffer_id, colors, BufferTypes::Colors, DrwImagesV::kLocationColor);
      renderer->UpdateData(uv_buffer_id, uvs, BufferTypes::Uvs, DrwImagesV::kLocationUv);
      glDrawElements(GL_TRIANGLE_FAN, RendBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
      renderer->UseVAOEnd();
   }
#endif
#endif

}

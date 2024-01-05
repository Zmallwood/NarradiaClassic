#pragma once

#include "Rend_Core.h"
#include "Calc.h"

namespace Narradia
{

   // View
#if 1
   class RendGrndV : public RendBaseV, public S<RendGrndV> {
     public:
      RendGrndV();
      ~RendGrndV();

      auto is_batch_drawing() {
         return is_batch_drawing_;
      }

      void set_is_batch_drawing(bool value) {
         is_batch_drawing_ = value;
      }

      auto location_projection() {
         return location_projection_;
      }

      auto location_view() {
         return location_view_;
      }

      auto location_model() {
         return location_model_;
      }

      auto location_alpha() {
         return location_alpha_;
      }

      auto location_view_pos() {
         return location_view_pos_;
      }

      auto location_fog_color() {
         return location_fog_color_;
      }

      auto fog_color_ground() {
         return fog_color_ground_;
      }

      void set_fog_color_ground(Color value) {
         fog_color_ground_ = value;
      }

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
      static constexpr int kLocationNormal = 3;

     private:
      int location_projection_ = -1;
      int location_view_ = -1;
      int location_model_ = -1;
      int location_alpha_ = -1;
      int location_view_pos_ = -1;
      int location_fog_color_ = -1;
      Color fog_color_ground_;
      bool is_batch_drawing_ = false;
   };

   // Free functions
#if 1
   RenderID NewTile();
   RenderID NewTileSurface();
   void SetTileGeom(RenderID vao_id, Square<Vertex3F> &verts);
   void SetTileSufaceGeom(RenderID vao_id, Vec<Vec<Square<Vertex3F>>> & verts);
   void DrawTileSurface(StringView image_name, RenderID vao_id, bool depth_test_off = false);
   inline void DrawTile(StringView image_name, RenderID vao_id, bool depth_test_off = false) {

      auto vertex_count = 4;
      auto renderer = RendGrndV::get();

      if (depth_test_off)
         glDisable(GL_DEPTH_TEST);
      else
         glEnable(GL_DEPTH_TEST);

      if (!renderer->is_batch_drawing()) {

         renderer->UseVAOBegin(vao_id);
         glUniformMatrix4fv(
             renderer->location_projection(), 1, GL_FALSE,
             glm::value_ptr(CameraGL::get()->persp_matrix()));
         glUniformMatrix4fv(
             renderer->location_view(), 1, GL_FALSE,
             glm::value_ptr(CameraGL::get()->view_matrix()));
         glm::mat4 model(1.0);
         glUniformMatrix4fv(renderer->location_model(), 1, GL_FALSE, glm::value_ptr(model));
         glUniform1f(renderer->location_alpha(), 1.0f);
         auto player_pos = Hero::get()->pos().Multiply(kTileSize);
         glm::vec3 view_pos(
             player_pos.x,
             player_pos.y +
                 CalcTileAverageElevation(
                     Hero::get()->pos().GetXZ().ToIntPoint(), Hero::get()->world_location()),
             player_pos.z);
         glUniform3fv(renderer->location_view_pos(), 1, glm::value_ptr(view_pos));
         glm::vec3 fog_color_gl(
             RendGrndV::get()->fog_color_ground().r, RendGrndV::get()->fog_color_ground().g,
             RendGrndV::get()->fog_color_ground().b);
         glUniform3fv(renderer->location_fog_color(), 1, glm::value_ptr(fog_color_gl));
      }

      auto image_id = ImageBank::get()->GetImage(image_name);
      glBindTexture(GL_TEXTURE_2D, image_id);
      glBindVertexArray(vao_id);
      glDrawElements(GL_TRIANGLE_FAN, vertex_count, GL_UNSIGNED_INT, NULL);
      glBindVertexArray(0);

      if (!renderer->is_batch_drawing())
         renderer->UseVAOEnd();
   }
   void StartTileBatchDrawing();
   void StopTileBatchDrawing();
#endif
#endif

}

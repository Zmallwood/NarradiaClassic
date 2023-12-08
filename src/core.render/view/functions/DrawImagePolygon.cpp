#include "DrawImagePolygon.h"
#include "../CameraGL.h"
#include "../RendererTilesView.h"
#include "core.assets/model/ImageBank.h"
#include "world.actors/model/Player.h"

namespace Narradia {

    void DrawImagePolygon(
        std::string_view image_name, RenderId vao_id, int vertex_count, bool depth_test_off) {

        auto renderer = RendererTilesView::Get();

        if (depth_test_off)
            glDisable(GL_DEPTH_TEST);
        else
            glEnable(GL_DEPTH_TEST);

        if (!renderer->is_batch_drawing()) {
            renderer->UseVaoBegin(vao_id);
            glUniformMatrix4fv(
                renderer->location_projection(), 1, GL_FALSE,
                glm::value_ptr(CameraGL::Get()->perspective_matrix()));
            glUniformMatrix4fv(
                renderer->location_view(), 1, GL_FALSE,
                glm::value_ptr(CameraGL::Get()->view_matrix()));
            glm::mat4 model(1.0);
            glUniformMatrix4fv(renderer->location_model(), 1, GL_FALSE, glm::value_ptr(model));
            glUniform1f(renderer->location_alpha(), 1.0f);
            glm::vec3 view_pos(
                Player::Get()->position().x, Player::Get()->position().y,
                Player::Get()->position().z);
            glUniform3fv(renderer->location_view_pos(), 1, glm::value_ptr(view_pos));
            glm::vec3 fog_color_gl(
                RendererTilesView::kFogColorGround.r, RendererTilesView::kFogColorGround.g,
                RendererTilesView::kFogColorGround.b);
            glUniform3fv(renderer->location_fog_color(), 1, glm::value_ptr(fog_color_gl));
        }

        auto image_id = ImageBank::Get()->GetImage(image_name);
        glBindTexture(GL_TEXTURE_2D, image_id);
        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLE_FAN, vertex_count, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);

        if (!renderer->is_batch_drawing())
            renderer->UseVaoEnd();
    }
}

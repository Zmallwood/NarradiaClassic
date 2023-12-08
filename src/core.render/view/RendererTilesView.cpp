#include "RendererTilesView.h"
#include "CameraGL.h"
#include "core.assets/model/ImageBank.h"
#include "functions/SetImagePolygonGeometry.h"
#include "world.actors/model/Player.h"
#include "functions/DrawImagePolygon.h"

namespace Narradia {
    RendererTilesView::RendererTilesView() {
        const GLchar *vertex_shader_source =
#include "core.render.shaders/model/TilesVertex.glsl"
            ;
        const GLchar *fragment_shader_source =
#include "core.render.shaders/model/TilesFragment.glsl"
            ;
        GetShaderProgramView()->Create(vertex_shader_source, fragment_shader_source);
        location_projection_ = GetUniformLocation("projection");
        location_view_ = GetUniformLocation("view");
        location_model_ = GetUniformLocation("model");
        location_alpha_ = GetUniformLocation("mAlpha");
        location_view_pos_ = GetUniformLocation("viewPos");
        location_fog_color_ = GetUniformLocation("fogColor");
    }

    void RendererTilesView::UpdateDrawTile(
        std::string_view image_name, RenderId vao_id, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2,
        Vertex3F &v3, Point3F &normal00, Point3F &normal10, Point3F &normal11, Point3F &normal01,
        bool depth_test_off) const {
        std::vector<Vertex3F> vertices;
        v0.normal = normal00;
        v1.normal = normal10;
        v2.normal = normal11;
        v3.normal = normal01;
        vertices.push_back(v0);
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        SetImagePolygonGeometry(vao_id, vertices);
        DrawImagePolygon(image_name, vao_id, 4, depth_test_off);
    }

    void RendererTilesView::StartBatchDrawing() {
        is_batch_drawing_ = true;
        glUseProgram(GetShaderProgramView()->shader_program()->program_id());
        glUniformMatrix4fv(
            location_projection_, 1, GL_FALSE,
            glm::value_ptr(CameraGL::Get()->perspective_matrix()));
        glUniformMatrix4fv(
            location_view_, 1, GL_FALSE, glm::value_ptr(CameraGL::Get()->view_matrix()));
        glm::mat4 model(1.0);
        glUniformMatrix4fv(location_model_, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1f(location_alpha_, 1.0f);
        glm::vec3 view_pos(
            Player::Get()->position().x, Player::Get()->position().y, Player::Get()->position().z);
        glUniform3fv(location_view_pos_, 1, glm::value_ptr(view_pos));
        glm::vec3 fog_color_gl(kFogColorGround.r, kFogColorGround.g, kFogColorGround.b);
        glUniform3fv(location_fog_color_, 1, glm::value_ptr(fog_color_gl));
        glUseProgram(GetShaderProgramView()->shader_program()->program_id());
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    }

    void RendererTilesView::StopBatchDrawing() {
        is_batch_drawing_ = false;
        glUseProgram(0);
        glDisable(GL_CULL_FACE);
    }

    RendererTilesView::~RendererTilesView() {
        CleanupBase();
    }
}

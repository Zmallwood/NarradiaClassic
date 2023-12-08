#include "RendererTilesView.h"
#include "CameraGL.h"
#include "core.assets/model/ImageBank.h"
#include "world.actors/model/Player.h"

namespace Narradia {
    RendererTilesView::RendererTilesView() {
        const GLchar *vertex_shader_source =
#include "core.render.shaders/model/TilesVertex.glsl"
            ;
        const GLchar *fragment_shader_source =
#include "core.render.shaders/model/TilesFragment.glsl"
            ;
        GetShaderProgramView()->Create(
            vertex_shader_source, fragment_shader_source);
        location_projection_ = GetUniformLocation("projection");
        location_view_ = GetUniformLocation("view");
        location_model_ = GetUniformLocation("model");
        location_alpha_ = GetUniformLocation("mAlpha");
        location_view_pos_ = GetUniformLocation("viewPos");
        location_fog_color_ = GetUniformLocation("fogColor");
    }

    RenderId RendererTilesView::NewImagePolygon(int num_vertices) {
        auto vertex_array_id = renderer_base_->GenerateNewVertexArrayId();
        auto index_buffer_id = renderer_base_->GenerateNewBufferId(
            BufferTypes::Indices, vertex_array_id);
        auto position_buffer_id = renderer_base_->GenerateNewBufferId(
            BufferTypes::Positions3D, vertex_array_id);
        auto color_buffer_id = renderer_base_->GenerateNewBufferId(
            BufferTypes::Colors, vertex_array_id);
        auto uv_buffer_id = renderer_base_->GenerateNewBufferId(
            BufferTypes::Uvs, vertex_array_id);
        auto normal_buffer_id = renderer_base_->GenerateNewBufferId(
            BufferTypes::Normals, vertex_array_id);
        glUseProgram(GetShaderProgramView()->shader_program()->program_id());
        SetIndicesData(index_buffer_id, num_vertices, nullptr);
        SetData(
            position_buffer_id, num_vertices, nullptr,
            BufferTypes::Positions3D);
        SetData(color_buffer_id, num_vertices, nullptr, BufferTypes::Colors);
        SetData(uv_buffer_id, num_vertices, nullptr, BufferTypes::Uvs);
        SetData(normal_buffer_id, num_vertices, nullptr, BufferTypes::Normals);
        glBindVertexArray(0);
        glUseProgram(0);
        return vertex_array_id;
    }

    RenderId RendererTilesView::NewTile() {
        return NewImagePolygon(4);
    }

    void RendererTilesView::SetGeometryTile(
        RenderId vao_id, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2, Vertex3F &v3,
        Point3F &normal00, Point3F &normal10, Point3F &normal11,
        Point3F &normal01) const {
        std::vector<Vertex3F> vertices;
        v0.normal = normal00;
        v1.normal = normal10;
        v2.normal = normal11;
        v3.normal = normal01;
        vertices.push_back(v0);
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        SetGeometryImagePolygon(vao_id, vertices);
    }

    void RendererTilesView::DrawTile(
        std::string_view image_name, RenderId vao_id,
        bool depth_test_off) const {
        DrawImagePolygon(image_name, vao_id, 4, depth_test_off);
    }

    void RendererTilesView::UpdateDrawTile(
        std::string_view image_name, RenderId vao_id, Vertex3F &v0,
        Vertex3F &v1, Vertex3F &v2, Vertex3F &v3, Point3F &normal00,
        Point3F &normal10, Point3F &normal11, Point3F &normal01,
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
        SetGeometryImagePolygon(vao_id, vertices);
        DrawImagePolygon(image_name, vao_id, 4, depth_test_off);
    }

    void RendererTilesView::SetGeometryImagePolygon(
        RenderId vao_id, std::vector<Vertex3F> &vertices) const {
        if (!is_batch_drawing_)
            glUseProgram(
                GetShaderProgramView()->shader_program()->program_id());
        std::vector<int> indices(vertices.size());
        std::iota(std::begin(indices), std::end(indices), 0);
        std::vector<float> positions;
        std::vector<float> colors;
        std::vector<float> uvs;
        std::vector<float> normals;
        for (auto &vertex : vertices) {
            positions.push_back(vertex.position.x);
            positions.push_back(vertex.position.y);
            positions.push_back(vertex.position.z);
            colors.push_back(vertex.color.r);
            colors.push_back(vertex.color.g);
            colors.push_back(vertex.color.b);
            colors.push_back(vertex.color.a);
            uvs.push_back(vertex.uv.x);
            uvs.push_back(vertex.uv.y);
            auto vertex_normal = vertex.normal;
            normals.push_back(vertex_normal.x);
            normals.push_back(vertex_normal.y);
            normals.push_back(vertex_normal.z);
        }
        auto index_buffer_id =
            renderer_base_->GetBufferId(BufferTypes::Indices, vao_id);
        auto position_buffer_id =
            renderer_base_->GetBufferId(BufferTypes::Positions3D, vao_id);
        auto color_buffer_id =
            renderer_base_->GetBufferId(BufferTypes::Colors, vao_id);
        auto uv_buffer_id =
            renderer_base_->GetBufferId(BufferTypes::Uvs, vao_id);
        auto normal_buffer_id =
            renderer_base_->GetBufferId(BufferTypes::Normals, vao_id);
        glBindVertexArray(vao_id);
        UpdateIndicesData(index_buffer_id, indices);
        UpdateData(
            position_buffer_id, positions, BufferTypes::Positions3D,
            kLocationPosition);
        UpdateData(
            color_buffer_id, colors, BufferTypes::Colors, kLocationColor);
        UpdateData(uv_buffer_id, uvs, BufferTypes::Uvs, kLocationUv);
        UpdateData(
            normal_buffer_id, normals, BufferTypes::Normals, kLocationNormal);
        glBindVertexArray(0);
        if (!is_batch_drawing_)
            glUseProgram(0);
    }

    void RendererTilesView::StartBatchDrawing() {
        is_batch_drawing_ = true;
        glUseProgram(GetShaderProgramView()->shader_program()->program_id());
        glUniformMatrix4fv(
            location_projection_, 1, GL_FALSE,
            glm::value_ptr(CameraGL::Get()->perspective_matrix()));
        glUniformMatrix4fv(
            location_view_, 1, GL_FALSE,
            glm::value_ptr(CameraGL::Get()->view_matrix()));
        glm::mat4 model(1.0);
        glUniformMatrix4fv(location_model_, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1f(location_alpha_, 1.0f);
        glm::vec3 view_pos(
            Player::Get()->position_3d().x, Player::Get()->position_3d().y,
            Player::Get()->position_3d().z);
        glUniform3fv(location_view_pos_, 1, glm::value_ptr(view_pos));
        glm::vec3 fog_color_gl(
            kFogColorGround.r, kFogColorGround.g, kFogColorGround.b);
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

    void RendererTilesView::DrawImagePolygon(
        std::string_view image_name, RenderId vao_id, int vertex_count,
        bool depth_test_off) const {
        if (depth_test_off)
            glDisable(GL_DEPTH_TEST);
        else
            glEnable(GL_DEPTH_TEST);
        if (!is_batch_drawing_) {
            glUseProgram(
                GetShaderProgramView()->shader_program()->program_id());
            glUniformMatrix4fv(
                location_projection_, 1, GL_FALSE,
                glm::value_ptr(CameraGL::Get()->perspective_matrix()));
            glUniformMatrix4fv(
                location_view_, 1, GL_FALSE,
                glm::value_ptr(CameraGL::Get()->view_matrix()));
            glm::mat4 model(1.0);
            glUniformMatrix4fv(
                location_model_, 1, GL_FALSE, glm::value_ptr(model));
            glUniform1f(location_alpha_, 1.0f);
            glm::vec3 view_pos(
                Player::Get()->position_3d().x, Player::Get()->position_3d().y,
                Player::Get()->position_3d().z);
            glUniform3fv(location_view_pos_, 1, glm::value_ptr(view_pos));
            glm::vec3 fog_color_gl(
                kFogColorGround.r, kFogColorGround.g, kFogColorGround.b);
            glUniform3fv(location_fog_color_, 1, glm::value_ptr(fog_color_gl));
            glUseProgram(
                GetShaderProgramView()->shader_program()->program_id());
        }
        auto image_id = ImageBank::Get()->GetImage(image_name);
        glBindTexture(GL_TEXTURE_2D, image_id);
        glBindVertexArray(vao_id);
        glDrawElements(GL_TRIANGLE_FAN, vertex_count, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);
        if (!is_batch_drawing_)
            glUseProgram(0);
    }

    RendererTilesView::~RendererTilesView() {
        CleanupBase();
    }
}

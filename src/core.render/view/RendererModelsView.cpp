#include "RendererModelsView.h"
#include "CameraGL.h"
#include "conf/model/Configuration.h"
#include "core.assets/model/ImageBank.h"
#include "core.assets/model/ModelBank.h"
#include "core.render.shaders/model/ModelsFragment.inc.cpp"
#include "core.render.shaders/model/ModelsVertex.inc.cpp"
#include "world.actors/model/Player.h"

namespace Narradia {
    RendererModelsView::RendererModelsView() {
        GetShaderProgramView()->Create(vertex_shader_source, fragment_shader_source);
        location_view_ = GetUniformLocation("view");
        location_projection_ = GetUniformLocation("projection");
        location_alpha_ = GetUniformLocation("mAlpha");
        location_model_ = GetUniformLocation("model");
        location_model_no_translation_ = GetUniformLocation("modelNoTranslation");
        location_color_mod_ = GetUniformLocation("mColorMod");
        location_view_pos_ = GetUniformLocation("viewPos");
        location_fog_color_ = GetUniformLocation("fogColor");
        location_no_fog_ = GetUniformLocation("noFog");
        location_no_lighting_ = GetUniformLocation("noLighting");
    }

    void RendererModelsView::NewModel(std::string_view model_name) {
        auto model = ModelBank::Get()->GetModel(model_name);
        model_ids_.insert({model_name.data(), std::map<int, std::map<float, const BodyData>>()});
        auto i_body = 0;
        for (auto &body : *model->model_parts()) {
            auto &timelines = body->timeline()->keyframes;
            for (auto &keyframe : timelines) {
                auto keyframe_time = keyframe.first;
                auto anim_key_body_keyframe = keyframe.second;
                auto vertex_count = anim_key_body_keyframe->vertices.size();
                auto body_keyframe_id = NewBodyKeyframe(model_name, keyframe_time, vertex_count);
                if (model_ids_.at(model_name.data()).count(i_body) == 0)
                    model_ids_.at(model_name.data()).insert({i_body, std::map<float, const BodyData>()});
                BodyData body_data;
                body_data.rid = body_keyframe_id;
                body_data.image_name = body->texture_name();
                body_data.num_vertices = vertex_count;
                model_ids_.at(model_name.data()).at(i_body).insert({keyframe_time, body_data});
                auto &model_keyframe = body->timeline()->keyframes.at(keyframe_time);
                std::vector<Vertex3F> vertices;
                std::vector<Point3F> normals;
                auto &anim_vertices = model_keyframe->vertices;
                for (auto v : anim_vertices) {
                    Vertex3F v3f;
                    v3f.position = v.position;
                    v3f.color = v.color;
                    v3f.uv = v.uv;
                    vertices.push_back(v3f);
                    Point3F n3f;
                    n3f.x = v.normal.x;
                    n3f.y = v.normal.y;
                    n3f.z = v.normal.z;
                    normals.push_back(n3f);
                }
                NewBodyKeyframeGeometry(
                    body->texture_name(), keyframe_time, body_keyframe_id, vertices, normals);
            }
            i_body++;
        }
    }

    RenderID RendererModelsView::NewBodyKeyframe(
        std::string_view model_name, float ms_time, int num_vertices) {
        auto vao_id = renderer_base_->GenerateNewVertexArrayId();
        if (timelines_.count(model_name) == 0)
            timelines_.insert({model_name, std::map<float, RenderID>()});
        timelines_.at(model_name).insert({ms_time, vao_id});
        return vao_id;
    }

    void RendererModelsView::NewBodyKeyframeGeometry(
        std::string_view image_name, float ms_time, RenderID vao_id, std::vector<Vertex3F> vertices,
        std::vector<Point3F> vertex_normals) {
        glEnable(GL_DEPTH_TEST);
        UseVaoBegin(vao_id);
        glUniformMatrix4fv(
            location_projection_, 1, GL_FALSE, value_ptr(CameraGL::Get()->perspective_matrix()));
        glUniformMatrix4fv(location_view_, 1, GL_FALSE, value_ptr(CameraGL::Get()->view_matrix()));
        glUniform1f(location_alpha_, 1.0f);
        auto image_id = ImageBank::Get()->GetImage(image_name);
        glBindTexture(GL_TEXTURE_2D, image_id);
        std::vector<int> indices(vertices.size());
        std::iota(std::begin(indices), std::end(indices), 0);
        std::vector<float> positions;
        std::vector<float> colors;
        std::vector<float> uvs;
        std::vector<float> normals;
        auto i = 0;
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
            if (vertex_normals.size() > i) {
                auto vertex_normal = vertex_normals.at(i);
                normals.push_back(vertex_normal.x);
                normals.push_back(-vertex_normal.y);
                normals.push_back(vertex_normal.z);
            }
            i++;
        }
        auto index_buffer_id = renderer_base_->GenerateNewBufferId(BufferTypes::Indices, vao_id);
        auto position_buffer_id =
            renderer_base_->GenerateNewBufferId(BufferTypes::Positions3D, vao_id);
        auto color_buffer_id = renderer_base_->GenerateNewBufferId(BufferTypes::Colors, vao_id);
        auto uv_buffer_id = renderer_base_->GenerateNewBufferId(BufferTypes::Uvs, vao_id);
        auto normal_buffer_id = renderer_base_->GenerateNewBufferId(BufferTypes::Normals, vao_id);
        auto num_vertices = vertices.size();
        SetIndicesData(index_buffer_id, num_vertices, indices.data());
        SetData(
            position_buffer_id, num_vertices, positions.data(), BufferTypes::Positions3D,
            kLocationPosition);
        SetData(color_buffer_id, num_vertices, colors.data(), BufferTypes::Colors, kLocationColor);
        SetData(uv_buffer_id, num_vertices, uvs.data(), BufferTypes::Uvs, kLocationUv);
        SetData(
            normal_buffer_id, num_vertices, normals.data(), BufferTypes::Normals, kLocationNormal);
        UseVaoEnd();
    }

    void RendererModelsView::DrawModel(
        std::string_view model_name, float ms_time, Point3F position, float rotation, float scaling,
        float brightness, glm::vec3 color_mod, bool no_fog, bool no_lighting) const {
        if (model_ids_.count(model_name.data()) == 0)
            return;
        if (!is_batch_drawing_) {
            glEnable(GL_DEPTH_TEST);
            glUseProgram(GetShaderProgramView()->shader_program()->program_id());
            glUniformMatrix4fv(
                location_projection_, 1, GL_FALSE,
                value_ptr(CameraGL::Get()->perspective_matrix()));
            glUniformMatrix4fv(
                location_view_, 1, GL_FALSE, glm::value_ptr(CameraGL::Get()->view_matrix()));
        }
        auto model_matrix = glm::rotate(
            glm::scale(
                glm::translate(glm::mat4(1.0), glm::vec3(position.x, position.y, position.z)),
                glm::vec3(scaling, scaling, scaling)),
            glm::radians(rotation), glm::vec3(0, 1, 0));
        auto model_no_translation_matrix = glm::rotate(
            glm::scale(
                glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0)),
                glm::vec3(scaling, scaling, scaling)),
            glm::radians(rotation), glm::vec3(0, 1, 0));
        glUniformMatrix4fv(location_model_, 1, GL_FALSE, glm::value_ptr(model_matrix));
        glUniformMatrix4fv(
            location_model_no_translation_, 1, GL_FALSE,
            glm::value_ptr(model_no_translation_matrix));
        glUniform3fv(location_color_mod_, 1, glm::value_ptr(color_mod));
        auto player_space_coord = Player::Get()->position().Multiply(kTileSize);
        glm::vec3 viewPos(player_space_coord.x, player_space_coord.y, player_space_coord.z);
        glUniform3fv(location_view_pos_, 1, glm::value_ptr(viewPos));
        glm::vec3 fogColorGl(kFogColorModels.r, kFogColorModels.g, kFogColorModels.b);
        glUniform3fv(location_fog_color_, 1, glm::value_ptr(fogColorGl));
        glUniform1f(location_alpha_, brightness);
        glUniform1f(location_no_fog_, no_fog ? 1.0f : 0.0f);
        glUniform1f(location_no_lighting_, no_lighting ? 1.0f : 0.0f);
        auto &all_nodes = model_ids_.at(model_name.data());
        auto p_model = ModelBank::Get()->GetModel(model_name);
        int ms_time_used;
        if (p_model->anim_duration() == 0)
            ms_time_used = 0;
        else
            ms_time_used =
                static_cast<int>(ms_time * global_animation_speed_) % p_model->anim_duration();
        auto &model_data = all_nodes;
        for (auto &entry : all_nodes) {
            auto &timeline = entry.second;
            auto found_time = -1.0f;
            const BodyData *p_body_data = nullptr;
            for (auto &keyframe : timeline) {
                auto time = keyframe.first;
                if (ms_time_used >= time)
                    found_time = time;
            }
            auto &body_data = timeline.at(found_time);
            glBindVertexArray(body_data.rid);
            auto image_id = ImageBank::Get()->GetImage(body_data.image_name);
            glBindTexture(GL_TEXTURE_2D, image_id);
            glDrawElements(GL_TRIANGLES, body_data.num_vertices, GL_UNSIGNED_INT, NULL);
        }
        glBindVertexArray(0);
        if (!is_batch_drawing_)
            glUseProgram(0);
    }

    void RendererModelsView::DrawModelsMany(
        std::string_view model_name, float ms_time, std::vector<Point3F> positions,
        std::vector<float> rotations, std::vector<float> scalings, std::vector<float> brightnesses,
        std::vector<glm::vec3> color_mods) const {
        if (model_ids_.count(model_name.data()) == 0)
            return;
        if (!is_batch_drawing_) {
            glEnable(GL_DEPTH_TEST);
            glUseProgram(GetShaderProgramView()->shader_program()->program_id());
            glUniformMatrix4fv(
                location_projection_, 1, GL_FALSE,
                value_ptr(CameraGL::Get()->perspective_matrix()));
            glUniformMatrix4fv(
                location_view_, 1, GL_FALSE, glm::value_ptr(CameraGL::Get()->view_matrix()));
        }
        auto &all_nodes = model_ids_.at(model_name.data());
        auto p_model = ModelBank::Get()->GetModel(model_name.data());
        int ms_time_used;
        if (p_model->anim_duration() == 0)
            ms_time_used = 0;
        else
            ms_time_used =
                static_cast<int>(ms_time * global_animation_speed_) % p_model->anim_duration();
        auto &model_data = all_nodes;
        for (auto &entry : all_nodes) {
            auto &timeline = entry.second;
            auto found_time = -1.0f;
            const BodyData *p_body_data = nullptr;
            for (auto &keyframe : timeline) {
                auto time = keyframe.first;
                if (ms_time_used >= time)
                    found_time = time;
            }
            auto &body_data = timeline.at(found_time);
            auto image_id = ImageBank::Get()->GetImage(body_data.image_name);
            for (auto i = 0; i < positions.size(); i++) {
                auto position = positions.at(i);
                auto rotation = rotations.at(i);
                auto scaling = scalings.at(i);
                auto colorMod = color_mods.at(i);
                auto brightness = brightnesses.at(i);
                auto model_matrix = glm::rotate(
                    glm::scale(
                        glm::translate(
                            glm::mat4(1.0), glm::vec3(position.x, position.y, position.z)),
                        glm::vec3(scaling, scaling, scaling)),
                    glm::radians(rotation), glm::vec3(0, 1, 0));
                auto model_no_translation_matrix = glm::rotate(
                    glm::scale(
                        glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0)),
                        glm::vec3(scaling, scaling, scaling)),
                    glm::radians(rotation), glm::vec3(0, 1, 0));
                glUniformMatrix4fv(location_model_, 1, GL_FALSE, glm::value_ptr(model_matrix));
                glUniformMatrix4fv(
                    location_model_no_translation_, 1, GL_FALSE,
                    glm::value_ptr(model_no_translation_matrix));
                glUniform3fv(location_color_mod_, 1, glm::value_ptr(colorMod));
                auto player_space_coord = Player::Get()->position().Multiply(kTileSize);
                glm::vec3 viewPos(player_space_coord.x, player_space_coord.y, player_space_coord.z);
                glUniform3fv(location_view_pos_, 1, glm::value_ptr(viewPos));
                glm::vec3 fogColorGl(kFogColorModels.r, kFogColorModels.g, kFogColorModels.b);
                glUniform3fv(location_fog_color_, 1, glm::value_ptr(fogColorGl));
                glUniform1f(location_alpha_, brightness);
                glUniform1f(location_no_fog_, 0.0f);
                glUniform1f(location_no_lighting_, 0.0f);
                glBindVertexArray(body_data.rid);
                glBindTexture(GL_TEXTURE_2D, image_id);
                glDrawElements(GL_TRIANGLES, body_data.num_vertices, GL_UNSIGNED_INT, NULL);
            }
        }
        glBindVertexArray(0);
        if (!is_batch_drawing_)
            glUseProgram(0);
    }

    void RendererModelsView::StartBatchDrawing() {
        is_batch_drawing_ = true;
        glEnable(GL_DEPTH_TEST);
        glUseProgram(GetShaderProgramView()->shader_program()->program_id());
        glUniformMatrix4fv(
            location_projection_, 1, GL_FALSE, value_ptr(CameraGL::Get()->perspective_matrix()));
        glUniformMatrix4fv(
            location_view_, 1, GL_FALSE, glm::value_ptr(CameraGL::Get()->view_matrix()));
    }

    void RendererModelsView::StopBatchDrawing() {
        is_batch_drawing_ = false;
    }

    RendererModelsView::~RendererModelsView() {
        CleanupBase();
    }
}

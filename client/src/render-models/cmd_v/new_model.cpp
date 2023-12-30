#if 1
#include "new_model.h"
#include "assets.h"
#include "new_body_keyframe.h"
#include "new_body_keyframe_geometry.h"
#include "render-models/renderer_models_v.h"
#endif

namespace Narradia
{
   auto NewModel(std::string_view model_name) -> void {
      auto renderer = RendererModelsV::get();
      auto model = ModelBank::get()->GetModel(model_name);
      auto model_ids = renderer->model_ids();
      model_ids->insert({model_name.data(), std::map<int, std::map<float, const BodyData>>()});
      auto i_body = 0;
      for (auto &body : *model->model_parts()) {
         auto &timelines = body->timeline()->keyframes;
         for (auto &keyframe : timelines) {
            auto keyframe_time = keyframe.first;
            auto anim_key_body_keyframe = keyframe.second;
            auto vertex_count = anim_key_body_keyframe->vertices.size();
            auto body_keyframe_id = NewBodyKeyframe(model_name, keyframe_time);
            if (model_ids->at(model_name.data()).count(i_body) == 0)
               model_ids->at(model_name.data()).insert({i_body, std::map<float, const BodyData>()});
            BodyData body_data;
            body_data.rid = body_keyframe_id;
            body_data.image_name = body->texture_name();
            body_data.num_vertices = vertex_count;
            model_ids->at(model_name.data()).at(i_body).insert({keyframe_time, body_data});
            auto &model_keyframe = body->timeline()->keyframes.at(keyframe_time);
            std::vector<Vertex3F> vertices;
            std::vector<Point3F> normals;
            auto &anim_vertices = model_keyframe->vertices;
            for (auto v : anim_vertices) {
               Vertex3F v3f;
               v3f.pos = v.pos;
               v3f.color = v.color;
               v3f.uv = v.uv;
               vertices.push_back(v3f);
               Point3F n3f;
               n3f.x = v.normal.x;
               n3f.y = v.normal.y;
               n3f.z = v.normal.z;
               normals.push_back(n3f);
            }
            NewBodyKeyframeGeometry(body_keyframe_id, vertices, normals);
         }
         i_body++;
      }
   }
}

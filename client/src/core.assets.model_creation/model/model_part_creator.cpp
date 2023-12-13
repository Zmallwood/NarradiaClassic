#include "model_part_creator.h"
namespace Narradia
{
   auto ModelPartCreator::TexNames(const aiScene *scene) const {
      std::vector<std::string> texture_names;
      auto num_materials = scene->mNumMaterials;
      for (auto i = 0; i < num_materials; i++) {
         aiString texture_name_cstr;
         scene->mMaterials[i]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), texture_name_cstr);
         auto texture_name = std::string(texture_name_cstr.C_Str());
         auto texture_name_no_extension = texture_name.substr(0, texture_name.length() - 4);
         texture_names.push_back(texture_name_no_extension);
      }
      return texture_names;
   }

   auto ModelPartCreator::TexNameForMesh(const aiScene *scene, aiMesh *mesh) const {
      auto texture_names = TexNames(scene);
      auto material = mesh->mMaterialIndex;
      auto texture_name = texture_names.at(material);
      return texture_name;
   }

   auto ModelPartCreator::Transformations(const aiScene *scene) const {
      auto root_node = scene->mRootNode;
      auto num_nodes = root_node->mNumChildren;
      auto node_name_to_transformations = std::map<std::shared_ptr<std::string>, aiMatrix4x4>();
      for (auto i = 0; i < num_nodes; i++) {
         auto node = root_node->mChildren[i];
         auto node_name = node->mName;
         auto node_transformation = node->mTransformation;
         node_name_to_transformations.insert(
             {std::make_shared<std::string>(node_name.C_Str()), node_transformation});
      }
      return node_name_to_transformations;
   }

   auto ModelPartCreator::NodeTransformation(const aiScene *scene, std::string node_name) const {
      auto all_transformations = Transformations(scene);
      for (auto &alpha : all_transformations) {
         if (*alpha.first == node_name.data())
            return alpha.second;
      }
      return aiMatrix4x4();
   }

   auto ModelPartCreator::Translate(Point3F *position, aiVectorKey position_keyframe) const {
      auto translation_matrix = aiMatrix4x4();
      translation_matrix[0][3] = position_keyframe.mValue.x;
      translation_matrix[1][3] = position_keyframe.mValue.y;
      translation_matrix[2][3] = position_keyframe.mValue.z;
      translation_matrix[0][0] = 1;
      translation_matrix[1][1] = 1;
      translation_matrix[2][2] = 1;
      translation_matrix[3][3] = 1;
      auto ai_position = aiVector3D{position->x, position->y, position->z};
      ai_position = translation_matrix * ai_position;
      *position = {-ai_position.x, ai_position.y, ai_position.z};
   }

   auto ModelPartCreator::Position(
       aiVector3D vertex, aiMatrix4x4 node_transformation, aiVectorKey position_keyframe,
       aiQuatKey rotation_keyframe, aiVectorKey scaling_keyframe) const {
      aiVector3D ai_position = {vertex.x, vertex.y, vertex.z};
      ai_position.x *= scaling_keyframe.mValue.x;
      ai_position.y *= scaling_keyframe.mValue.y;
      ai_position.z *= scaling_keyframe.mValue.z;
      ai_position = rotation_keyframe.mValue.GetMatrix() * ai_position;
      ai_position = node_transformation * ai_position;
      auto position = Point3F{ai_position.x, ai_position.y, ai_position.z};
      Translate(&position, position_keyframe);
      ai_position = {position.x, position.y, position.z};
      position = {ai_position.x, ai_position.y, ai_position.z};
      float temp;
      temp = position.y;
      position.y = position.z;
      position.z = temp;
      return position;
   }

   auto ModelPartCreator::NewModelPartKeyframe(
       const aiScene *scene, std::string node_name, aiMesh *mesh, aiVectorKey position_keyframe,
       aiQuatKey rotation_keyframe, aiVectorKey scaling_keyframe) const {
      auto new_model_part_keyframe = std::make_shared<ModelPartKeyframe>();
      auto node_transformation = NodeTransformation(scene, node_name);
      auto num_vertices = mesh->mNumVertices;
      for (auto i = 0; i < num_vertices; i++) {
         auto mesh_vertex = mesh->mVertices[i];
         auto mesh_normal = mesh->mNormals[i];
         auto mesh_uv = mesh->mTextureCoords[0][i];
         auto position = Position(
             mesh_vertex, node_transformation, position_keyframe, rotation_keyframe,
             scaling_keyframe);
         auto color = Color{0.0f, 0.0f, 0.0f, 0.0f};
         auto normal = Position(
             mesh_normal, node_transformation, position_keyframe, rotation_keyframe,
             scaling_keyframe);
         auto uv = PointF{1.0f - mesh_uv.x, 1.0f - mesh_uv.y};
         Vertex3F anim_vertex;
         anim_vertex.position = position;
         anim_vertex.color = color;
         anim_vertex.normal = normal;
         anim_vertex.uv = uv;
         new_model_part_keyframe->vertices.push_back(anim_vertex);
      }
      return new_model_part_keyframe;
   }

   auto ModelPartCreator::CreateModelPartFromMesh(
       const aiScene *scene, std::string node_name, aiMesh *mesh) const
       -> std::shared_ptr<ModelPart> {
      auto new_model_part = std::make_shared<ModelPart>();
      auto tex_name = TexNameForMesh(scene, mesh);
      new_model_part->set_texture_name(tex_name);
      auto no_keyframe_at_time_0_exists =
          ModelPartKeyframeCreator::get()->GetPositionKeyframe(scene, node_name, 0).mTime > 0;
      auto num_keyframes =
          ModelPartKeyframeCreator::get()->GetNodePositionKeyframes(scene, node_name).size();
      for (auto k = 0; k < num_keyframes; k++) {
         auto position_keyframe =
             ModelPartKeyframeCreator::get()->GetPositionKeyframe(scene, node_name, k);
         auto rotation_keyframe =
             ModelPartKeyframeCreator::get()->GetRotationKeyframe(scene, node_name, k);
         auto scaling_keyframe =
             ModelPartKeyframeCreator::get()->GetScalingKeyframe(scene, node_name, k);
         auto keyframe_time = static_cast<float>(position_keyframe.mTime);
         auto new_model_part_keyframe = NewModelPartKeyframe(
             scene, node_name, mesh, position_keyframe, rotation_keyframe, scaling_keyframe);
         new_model_part->timeline()->keyframes.insert({keyframe_time, new_model_part_keyframe});
         if (no_keyframe_at_time_0_exists && k == 0)
            new_model_part->timeline()->keyframes.insert({0.0f, new_model_part_keyframe});
      }
      return new_model_part;
   }

}

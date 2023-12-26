#include "model_part_creator.h"
namespace Narradia
{
   auto ModelPartCreator::TexNames(const aiScene *raw_model) const
   {
      std::vector<std::string> tex_names;
      auto num_materials = raw_model->mNumMaterials;
      for (auto i = 0; i < num_materials; i++)
      {
         aiString tex_name_cstr;
         raw_model->mMaterials[i]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), tex_name_cstr);
         auto tex_name = std::string(tex_name_cstr.C_Str());
         auto tex_name_no_extension = tex_name.substr(0, tex_name.length() - 4);
         tex_names.push_back(tex_name_no_extension);
      }
      return tex_names;
   }

   auto ModelPartCreator::TexNameForMesh(const aiScene *raw_model, aiMesh *mesh) const
   {
      auto tex_names = TexNames(raw_model);
      auto material = mesh->mMaterialIndex;
      auto tex_name = tex_names.at(material);
      return tex_name;
   }

   auto ModelPartCreator::Transformations(const aiScene *raw_model) const
   {
      auto root_node = raw_model->mRootNode;
      auto num_nodes = root_node->mNumChildren;
      auto node_name_to_transformations = std::map<std::shared_ptr<std::string>, aiMatrix4x4>();
      for (auto i = 0; i < num_nodes; i++)
      {
         auto node = root_node->mChildren[i];
         auto node_name = node->mName;
         auto node_transformation = node->mTransformation;
         node_name_to_transformations.insert(
             {std::make_shared<std::string>(node_name.C_Str()), node_transformation});
      }
      return node_name_to_transformations;
   }

   auto ModelPartCreator::NodeTransformation(const aiScene *raw_model, std::string node_name) const
   {
      auto all_transformations = Transformations(raw_model);
      for (auto &alpha : all_transformations)
      {
         if (*alpha.first == node_name.data())
            return alpha.second;
      }
      return aiMatrix4x4();
   }

   auto ModelPartCreator::Translate(Point3F *position, aiVectorKey position_keyframe) const
   {
      auto transl_mat = aiMatrix4x4();
      transl_mat[0][3] = position_keyframe.mValue.x;
      transl_mat[1][3] = position_keyframe.mValue.y;
      transl_mat[2][3] = position_keyframe.mValue.z;
      transl_mat[0][0] = 1;
      transl_mat[1][1] = 1;
      transl_mat[2][2] = 1;
      transl_mat[3][3] = 1;
      auto ai_position = aiVector3D{position->x, position->y, position->z};
      ai_position = transl_mat * ai_position;
      *position = {-ai_position.x, ai_position.y, ai_position.z};
   }

   auto ModelPartCreator::Position(
       aiVector3D vertex, aiMatrix4x4 node_transformation, aiVectorKey position_keyframe,
       aiQuatKey rotation_keyframe, aiVectorKey scaling_keyframe) const
   {
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
       const aiScene *raw_model, std::string node_name, aiMesh *mesh, aiVectorKey position_keyframe,
       aiQuatKey rotation_keyframe, aiVectorKey scaling_keyframe) const
   {
      auto new_model_part_keyframe = std::make_shared<Keyframe>();
      auto node_transformation = NodeTransformation(raw_model, node_name);
      auto num_vertices = mesh->mNumVertices;
      for (auto i = 0; i < num_vertices; i++)
      {
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
       const aiScene *raw_model, std::string node_name, aiMesh *mesh) const
       -> std::shared_ptr<ModelPart>
   {
      auto new_model_part = std::make_shared<ModelPart>();
      auto tex_name = TexNameForMesh(raw_model, mesh);
      new_model_part->set_texture_name(tex_name);
      auto no_keyframe_at_time_0_exists =
          KeyframeCreator::get()->PositionKeyframe(raw_model, node_name, 0).mTime > 0;
      auto num_keyframes =
          KeyframeCreator::get()->NodePositionKeyframes(raw_model, node_name).size();
      for (auto k = 0; k < num_keyframes; k++)
      {
         auto position_keyframe = KeyframeCreator::get()->PositionKeyframe(raw_model, node_name, k);
         auto rotation_keyframe = KeyframeCreator::get()->RotationKeyframe(raw_model, node_name, k);
         auto scaling_keyframe = KeyframeCreator::get()->ScalingKeyframe(raw_model, node_name, k);
         auto keyframe_time = static_cast<float>(position_keyframe.mTime);
         auto new_model_part_keyframe = NewModelPartKeyframe(
             raw_model, node_name, mesh, position_keyframe, rotation_keyframe, scaling_keyframe);
         new_model_part->timeline()->keyframes.insert({keyframe_time, new_model_part_keyframe});
         if (no_keyframe_at_time_0_exists && k == 0)
            new_model_part->timeline()->keyframes.insert({0.0f, new_model_part_keyframe});
      }
      return new_model_part;
   }

}

#if 1
#include "Model_Mk.h"
#include "Assets.h"
#endif

namespace Narradia
{

   // KeyframeCreator
#if 1
   // Keyframes
#if 1
   auto KeyframeCreator::PosKeyframe(
       const aiScene *raw_model, String node_name, int keyframe_index) const -> aiVectorKey {

      auto node_position_keyframes = NodePosKeyframes(raw_model, node_name);
      aiVectorKey position_keyframe;

      if (keyframe_index < node_position_keyframes.size())
         position_keyframe = node_position_keyframes.at(keyframe_index);
      else
         position_keyframe = *(node_position_keyframes.end() - 1);

      return position_keyframe;
   }

   auto KeyframeCreator::RotKeyframe(
       const aiScene *raw_model, String node_name, int keyframe_index) const -> aiQuatKey {

      auto node_rotation_keyframes = NodeRotKeyframes(raw_model, node_name);
      aiQuatKey rotation_keyframe;

      if (keyframe_index < node_rotation_keyframes.size())
         rotation_keyframe = node_rotation_keyframes.at(keyframe_index);
      else
         rotation_keyframe = *(node_rotation_keyframes.end() - 1);

      return rotation_keyframe;
   }

   auto KeyframeCreator::ScalKeyframe(
       const aiScene *raw_model, String node_name, int keyframe_index) const -> aiVectorKey {

      auto node_scaling_keyframes = NodeScalKeyframes(raw_model, node_name);
      aiVectorKey scaling_keyframe;

      if (keyframe_index < node_scaling_keyframes.size())
         scaling_keyframe = node_scaling_keyframes.at(keyframe_index);
      else
         scaling_keyframe = *(node_scaling_keyframes.end() - 1);

      return scaling_keyframe;
   }
#endif

   // Anim keyframes
#if 1
   auto KeyframeCreator::AnimPosKeyframes(const aiScene *raw_model) const {

      auto node_name_to_position_keyframes = Map<String, Vec<aiVectorKey>>();

      if (raw_model->mNumAnimations == 0) {

         auto num_meshes = raw_model->mNumMeshes;

         for (auto i = 0; i < num_meshes; i++) {

            auto mesh = raw_model->mMeshes[i];
            auto original_name = String(mesh->mName.C_Str());
            auto node_name = original_name.substr(0, original_name.length() - 5);
            Vec<aiVectorKey> position_keyframes;
            aiVectorKey position_keyframe;
            position_keyframe.mTime = 0.0;
            position_keyframe.mValue = aiVector3D(0.0, 0.0, 0.0);
            position_keyframes.push_back(position_keyframe);
            node_name_to_position_keyframes.insert({node_name.c_str(), position_keyframes});
         }
      }
      else {

         auto animation0 = raw_model->mAnimations[0];
         auto num_channels = animation0->mNumChannels;

         for (auto i = 0; i < num_channels; i++) {
            auto anim_channel = animation0->mChannels[i];
            auto node_name = String(anim_channel->mNodeName.C_Str());
            auto num_position_keys = anim_channel->mNumPositionKeys;
            Vec<aiVectorKey> position_keyframes;
            aiVectorKey original_position_keyframe;

            for (auto j = 0; j < num_position_keys; j++) {

               if (j == 0)
                  original_position_keyframe = anim_channel->mPositionKeys[j];

               auto position_keyframe = anim_channel->mPositionKeys[j];
               position_keyframe.mValue -= original_position_keyframe.mValue;
               position_keyframe.mValue.z *= -1;
               position_keyframes.push_back(position_keyframe);
            }

            if (num_position_keys > 0)
               node_name_to_position_keyframes.insert({node_name, position_keyframes});
         }
      }

      return node_name_to_position_keyframes;
   }

   auto KeyframeCreator::AnimRotKeyframes(const aiScene *raw_model) const {

      auto node_name_to_rotation_keyframes = Map<String, Vec<aiQuatKey>>();

      if (raw_model->mNumAnimations == 0) {

         auto num_meshes = raw_model->mNumMeshes;

         for (auto i = 0; i < num_meshes; i++) {

            auto mesh = raw_model->mMeshes[i];
            auto original_name = String(mesh->mName.C_Str());
            auto node_name = original_name.substr(0, original_name.length() - 5);
            Vec<aiQuatKey> rotation_keyframes;
            aiQuatKey rotation_keyframe;
            rotation_keyframe.mTime = 0.0;
            rotation_keyframe.mValue = aiQuaternion(0.0, 0.0, 0.0);
            rotation_keyframes.push_back(rotation_keyframe);
            node_name_to_rotation_keyframes.insert({node_name.c_str(), rotation_keyframes});
         }
      }
      else {

         auto animation0 = raw_model->mAnimations[0];
         auto num_channels = animation0->mNumChannels;

         for (auto i = 0; i < num_channels; i++) {

            auto anim_channel = animation0->mChannels[i];
            auto node_name = String(anim_channel->mNodeName.C_Str());
            auto num_rotation_keys = anim_channel->mNumRotationKeys;
            std::vector<aiQuatKey> rotation_keyframes;
            aiQuatKey original_rotation_keyframe;

            for (auto j = 0; j < num_rotation_keys; j++) {

               if (j == 0)
                  original_rotation_keyframe = anim_channel->mRotationKeys[j];

               auto rotation_keyframe = anim_channel->mRotationKeys[j];
               rotation_keyframe.mValue.x -= original_rotation_keyframe.mValue.x;
               rotation_keyframe.mValue.y -= original_rotation_keyframe.mValue.y;
               rotation_keyframe.mValue.z -= original_rotation_keyframe.mValue.z;
               rotation_keyframes.push_back(rotation_keyframe);
            }

            if (num_rotation_keys > 0)
               node_name_to_rotation_keyframes.insert({node_name, rotation_keyframes});
         }
      }
      return node_name_to_rotation_keyframes;
   }

   auto KeyframeCreator::AnimScalKeyframes(const aiScene *raw_model) const {
      auto node_name_to_scaling_keyframes = Map<String, Vec<aiVectorKey>>();

      if (raw_model->mNumAnimations == 0) {

         auto num_meshes = raw_model->mNumMeshes;

         for (auto i = 0; i < num_meshes; i++) {

            auto mesh = raw_model->mMeshes[i];
            auto original_name = String(mesh->mName.C_Str());
            auto node_name = original_name.substr(0, original_name.length() - 5);
            Vec<aiVectorKey> scaling_keyframes;
            aiVectorKey scaling_keyframe;
            scaling_keyframe.mTime = 0.0;
            scaling_keyframe.mValue = aiVector3D(1.0, -1.0, 1.0);
            scaling_keyframes.push_back(scaling_keyframe);
            node_name_to_scaling_keyframes.insert({node_name.c_str(), scaling_keyframes});
         }
      }
      else {

         auto animation0 = raw_model->mAnimations[0];
         auto num_channels = animation0->mNumChannels;

         for (auto i = 0; i < num_channels; i++) {

            auto anim_channel = animation0->mChannels[i];
            auto node_name = String(anim_channel->mNodeName.C_Str());
            auto num_scaling_keys = anim_channel->mNumScalingKeys;
            Vec<aiVectorKey> scaling_keyframes;
            aiVectorKey original_scaling_keyframe;

            for (auto j = 0; j < num_scaling_keys; j++) {

               if (j == 0)
                  original_scaling_keyframe = anim_channel->mScalingKeys[i];

               auto scaling_keyframe = anim_channel->mScalingKeys[j];
               scaling_keyframe.mValue.x /= original_scaling_keyframe.mValue.x;
               scaling_keyframe.mValue.y /= original_scaling_keyframe.mValue.y;
               scaling_keyframe.mValue.z /= original_scaling_keyframe.mValue.z;
               scaling_keyframes.push_back(scaling_keyframe);
            }

            if (num_scaling_keys > 0)
               node_name_to_scaling_keyframes.insert({node_name, scaling_keyframes});
         }
      }

      return node_name_to_scaling_keyframes;
   }
#endif

   // Node keyframes
#if 1
   auto KeyframeCreator::NodePosKeyframes(const aiScene *raw_model, String node_name) const
       -> Vec<aiVectorKey> {

      auto all_position_keyframes = AnimPosKeyframes(raw_model);
      Vec<aiVectorKey> node_position_keyframes;

      if (all_position_keyframes.count(node_name))
         node_position_keyframes = all_position_keyframes.at(node_name);

      auto num_position_keyframes = node_position_keyframes.size();
      auto num_max_keyframes = num_position_keyframes;

      if (num_max_keyframes == 0) {

         num_max_keyframes = 1;
         node_position_keyframes.push_back(aiVectorKey(0.0, aiVector3D()));
      }

      return node_position_keyframes;
   }

   auto KeyframeCreator::NodeRotKeyframes(const aiScene *raw_model, String node_name) const
       -> Vec<aiQuatKey> {

      auto all_rotation_keyframes = AnimRotKeyframes(raw_model);
      Vec<aiQuatKey> node_rotation_keyframes;

      if (all_rotation_keyframes.count(node_name))
         node_rotation_keyframes = all_rotation_keyframes.at(node_name);

      auto num_rotation_keyframes = node_rotation_keyframes.size();
      auto num_max_keyframes = num_rotation_keyframes;

      if (num_max_keyframes == 0) {

         num_max_keyframes = 1;
         node_rotation_keyframes.push_back(aiQuatKey(0.0, aiQuaternion()));
      }

      return node_rotation_keyframes;
   }

   auto KeyframeCreator::NodeScalKeyframes(const aiScene *raw_model, String node_name) const
       -> Vec<aiVectorKey> {

      auto all_scaling_keyframes = AnimScalKeyframes(raw_model);
      Vec<aiVectorKey> node_scaling_keyframes;

      if (all_scaling_keyframes.count(node_name))
         node_scaling_keyframes = all_scaling_keyframes.at(node_name);

      auto num_scaling_keyframes = node_scaling_keyframes.size();
      auto num_max_keyframes = num_scaling_keyframes;

      if (num_max_keyframes == 0) {

         num_max_keyframes = 1;
         node_scaling_keyframes.push_back(aiVectorKey(0.0, aiVector3D(1.0)));
      }

      return node_scaling_keyframes;
   }
#endif
#endif

   // ModelPartCreator
#if 1
   auto ModelPartCreator::TexNames(const aiScene *raw_model) const {

      Vec<String> tex_names;
      auto num_materials = raw_model->mNumMaterials;

      for (auto i = 0; i < num_materials; i++) {

         aiString tex_name_cstr;
         raw_model->mMaterials[i]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), tex_name_cstr);
         auto tex_name = std::string(tex_name_cstr.C_Str());
         auto tex_name_no_extension = tex_name.substr(0, tex_name.length() - 4);
         tex_names.push_back(tex_name_no_extension);
      }

      return tex_names;
   }

   auto ModelPartCreator::TexNameForMesh(const aiScene *raw_model, aiMesh *mesh) const {

      auto tex_names = TexNames(raw_model);
      auto material = mesh->mMaterialIndex;
      auto tex_name = tex_names.at(material);

      return tex_name;
   }

   auto ModelPartCreator::Transformations(const aiScene *raw_model) const {

      auto root_node = raw_model->mRootNode;
      auto num_nodes = root_node->mNumChildren;
      auto node_name_to_transformations = Map<SharedPtr<String>, aiMatrix4x4>();

      for (auto i = 0; i < num_nodes; i++) {

         auto node = root_node->mChildren[i];
         auto node_name = node->mName;
         auto node_transformation = node->mTransformation;
         node_name_to_transformations.insert(
             {MakeShared<String>(node_name.C_Str()), node_transformation});
      }

      return node_name_to_transformations;
   }

   auto ModelPartCreator::NodeTransformation(const aiScene *raw_model, String node_name) const {

      auto all_transformations = Transformations(raw_model);

      for (auto &alpha : all_transformations) {

         if (*alpha.first == node_name.data())
            return alpha.second;
      }

      return aiMatrix4x4();
   }

   auto ModelPartCreator::Translate(Point3F *position, aiVectorKey position_keyframe) const {

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
       const aiScene *raw_model, String node_name, aiMesh *mesh, aiVectorKey position_keyframe,
       aiQuatKey rotation_keyframe, aiVectorKey scaling_keyframe) const {

      auto new_model_part_keyframe = MakeShared<Keyframe>();
      auto node_transformation = NodeTransformation(raw_model, node_name);
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
         anim_vertex.pos = position;
         anim_vertex.color = color;
         anim_vertex.normal = normal;
         anim_vertex.uv = uv;
         new_model_part_keyframe->vertices.push_back(anim_vertex);
      }

      return new_model_part_keyframe;
   }

   auto ModelPartCreator::CreateModelPartFromMesh(
       const aiScene *raw_model, String node_name, aiMesh *mesh) const -> SharedPtr<ModelPart> {

      auto new_model_part = MakeShared<ModelPart>();
      auto tex_name = TexNameForMesh(raw_model, mesh);
      new_model_part->set_texture_name(tex_name);
      auto no_keyframe_at_time_0_exists =
          KeyframeCreator::get()->PosKeyframe(raw_model, node_name, 0).mTime > 0;
      auto num_keyframes = KeyframeCreator::get()->NodePosKeyframes(raw_model, node_name).size();

      for (auto k = 0; k < num_keyframes; k++) {

         auto position_keyframe = KeyframeCreator::get()->PosKeyframe(raw_model, node_name, k);
         auto rotation_keyframe = KeyframeCreator::get()->RotKeyframe(raw_model, node_name, k);
         auto scaling_keyframe = KeyframeCreator::get()->ScalKeyframe(raw_model, node_name, k);
         auto keyframe_time = static_cast<float>(position_keyframe.mTime);
         auto new_model_part_keyframe = NewModelPartKeyframe(
             raw_model, node_name, mesh, position_keyframe, rotation_keyframe, scaling_keyframe);
         new_model_part->timeline()->keyframes.insert({keyframe_time, new_model_part_keyframe});

         if (no_keyframe_at_time_0_exists && k == 0)
            new_model_part->timeline()->keyframes.insert({0.0f, new_model_part_keyframe});
      }

      return new_model_part;
   }
#endif

   // MeshObtainer
#if 1
   auto MeshObtainer::ModelMeshIds(const aiScene *raw_model) const
       -> Map<SharedPtr<String>, Vec<int>> {

      Map<SharedPtr<String>, Vec<int>> node_name_to_meshes;
      auto root_node = raw_model->mRootNode;
      auto num_sub_nodes = root_node->mNumChildren;

      for (auto i = 0; i < num_sub_nodes; i++) {

         auto sub_node = root_node->mChildren[i];
         auto sub_node_name = sub_node->mName;
         auto num_meshes = sub_node->mNumMeshes;
         Vec<int> meshes;

         for (auto j = 0; j < num_meshes; j++)
            meshes.push_back(sub_node->mMeshes[j]);

         const char *c_str = sub_node_name.C_Str();
         auto key = String{c_str};
         node_name_to_meshes.insert({MakeShared<String>(key), meshes});
      }

      return node_name_to_meshes;
   }

   auto MeshObtainer::NodeMeshes(const aiScene *raw_model, Vec<int> node_mesh_ids) const
       -> Vec<aiMesh *> {

      Vec<aiMesh *> node_meshes;
      auto num_meshes = node_mesh_ids.size();

      for (auto i = 0; i < num_meshes; i++) {

         auto mesh = raw_model->mMeshes[node_mesh_ids.at(i)];
         node_meshes.push_back(mesh);
      }

      return node_meshes;
   }
#endif

   // ModelCreator
#if 1
   auto ModelCreator::ModelParts(const aiScene *raw_model) {

      std::vector<std::shared_ptr<ModelPart>> all_model_parts;

      for (auto &entry : MeshObtainer::get()->ModelMeshIds(raw_model)) {

         std::string node_name = *entry.first;
         auto node_mesh_ids = entry.second;

         for (auto &mesh : MeshObtainer::get()->NodeMeshes(raw_model, node_mesh_ids)) {

            auto new_model_part =
                ModelPartCreator::get()->CreateModelPartFromMesh(raw_model, node_name, mesh);
            all_model_parts.push_back(new_model_part);
         }
      }

      return all_model_parts;
   }

   auto ModelCreator::CreateModel(const aiScene *raw_model) -> std::shared_ptr<Model> {

      auto anim_duration = raw_model->mNumAnimations > 0 ? raw_model->mAnimations[0]->mDuration : 0;
      auto new_model = std::make_shared<Model>(anim_duration);

      for (auto &model_part : ModelParts(raw_model))
         new_model->model_parts()->push_back(model_part);

      return new_model;
   }
#endif

}

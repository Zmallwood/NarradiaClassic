#pragma once
#include "../../core-model_structure/model/model_part.h"
#include "../../matter/model/color.h"
#include "../../matter/model/point3f.h"
#include "keyframe_creator.h"
#include <assimp/scene.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Creates ModelParts, belonging to a 3D model.
   ////////////////////////////////////////////////////////////////////////////////
   class ModelPartCreator : public Singleton<ModelPartCreator> {
     public:
      auto
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Creates and returns a new ModelPart from a raw assimp mesh, containing a timeline
      /// with all its keyframes, with applied animation transformations.
      ///
      /// @param[in] raw_model Raw assimp model the model is contained in.
      /// @param[in] node_name Node name for node the mesh belongs to.
      /// @param[in] mesh Raw assimp mesh to create the model part from.
      /// @return Created model part.
      ////////////////////////////////////////////////////////////////////////////////
      CreateModelPartFromMesh(const aiScene *raw_model, std::string node_name, aiMesh *mesh) const
          -> std::shared_ptr<ModelPart>;

     private:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets texture name for a certain mesh in an assimp model.
      ///
      /// @param[in] raw_model Raw assimp model.
      /// @param[in] mesh Assimp mesh to return the texture name for.
      /// @return The texture name.
      ////////////////////////////////////////////////////////////////////////////////
      auto TexNameForMesh(const aiScene *raw_model, aiMesh *mesh) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Creates and returns a new Keyframe from a raw assimp mesh, with applied node
      /// transformation, for the node it belongs to (provided by its name to the function), and
      /// position/rotation/scaling keyframes from animation.
      ///
      /// @param[in] raw_model Raw assimp model.
      /// @param[in] node_name Name of model the mesh belongs to.
      /// @param[in] mesh Raw assimp mesh.
      /// @param[in] position_keyframe Position keyframe from animation.
      /// @param[in] rotation_keyframe Rotation keyframe from animation.
      /// @param[in] scaling_keyframe Scaling keyframe from animation.
      /// @return Created keyframe.
      ////////////////////////////////////////////////////////////////////////////////
      auto NewModelPartKeyframe(
          const aiScene *raw_model, std::string node_name, aiMesh *mesh,
          aiVectorKey position_keyframe, aiQuatKey rotation_keyframe,
          aiVectorKey scaling_keyframe) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets names of all textures used in an assimp model.
      ///
      /// @param[in] raw_model Raw assimp model.
      /// @return The texture names.
      ////////////////////////////////////////////////////////////////////////////////
      auto TexNames(const aiScene *raw_model) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets transformation matrix in raw assimp model for node with certain name.
      ///
      /// @param[in] raw_model Raw assimp model.
      /// @param[in] node_name Node name to return the transformation matrix for.
      /// @return The transformation matrix.
      ////////////////////////////////////////////////////////////////////////////////
      auto NodeTransformation(const aiScene *raw_model, std::string node_name) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Returns position of a vector after having applied node transformation and
      /// position/rotation/scaling keyframe modifications (from animation).
      ///
      /// @param[in] vertex Vertex to transform.
      /// @param[in] node_transformation Transformation matrix for node the vector belongs to.
      /// @param[in] position_keyframe Position transformation data from animation.
      /// @param[in] rotation_keyframe Rotation transformation data from animation.
      /// @param[in] scaling_keyframe Scaling transformation data from animation.
      /// @return Transformed vector.
      ////////////////////////////////////////////////////////////////////////////////
      auto Position(
          aiVector3D vertex, aiMatrix4x4 node_transformation, aiVectorKey position_keyframe,
          aiQuatKey rotation_keyframe, aiVectorKey scaling_keyframe) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets all transformation matrices for an assimp model mapped by their node names in
      /// which they are used.
      ///
      /// @param[in] raw_model Raw assimp model.
      /// @return All transformation matrices mapped by their node names.
      ////////////////////////////////////////////////////////////////////////////////
      auto Transformations(const aiScene *raw_model) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Translates a position with a position vector for a keyframe.
      ///
      /// @param[in/out] position Pointer to point to translate, pointed value modified inside
      /// function.
      /// @param[in] position_keyframe Position vector for a keyframe to translate with.
      ////////////////////////////////////////////////////////////////////////////////
      auto Translate(Point3F *position, aiVectorKey position_keyframe) const;
   };
}

#pragma once
#include <assimp/scene.h>
#include <map>
#include <vector>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Creates keyframes, belonging to a 3D model.
   ////////////////////////////////////////////////////////////////////////////////
   class KeyframeCreator : public Singleton<KeyframeCreator> {
     public:
      auto
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets a position keyframe for a node in a model at a certain keyframe index.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @param[in] node_name Name of node.
      /// @param[int] keyframe_index Index for keyframe to return.
      /// @return The position keyframe.
      ////////////////////////////////////////////////////////////////////////////////
      PositionKeyframe(const aiScene *raw_model, std::string node_name, int keyframe_index) const
          -> aiVectorKey;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets a rotation keyframe for a node in a model at a certain keyframe index.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @param[in] node_name Name of node.
      /// @param[int] keyframe_index Index for keyframe to return.
      /// @return The rotation keyframe.
      ////////////////////////////////////////////////////////////////////////////////
      auto
      RotationKeyframe(const aiScene *raw_model, std::string node_name, int keyframe_index) const
          -> aiQuatKey;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets a scaling keyframe for a node in a model at a certain keyframe index.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @param[in] node_name Name of node.
      /// @param[int] keyframe_index Index for keyframe to return.
      /// @return The scaling keyframe.
      ////////////////////////////////////////////////////////////////////////////////
      auto
      ScalingKeyframe(const aiScene *raw_model, std::string node_name, int keyframe_index) const
          -> aiVectorKey;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets all position keyframes for a certain node in a model.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @param[in] node_name Name of node.
      /// @return All position keyframes for the node.
      ////////////////////////////////////////////////////////////////////////////////
      auto NodePositionKeyframes(const aiScene *raw_model, std::string node_name) const
          -> std::vector<aiVectorKey>;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets all rotation keyframes for a certain node in a model.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @param[in] node_name Name of node.
      /// @return All rotation keyframes for the node.
      ////////////////////////////////////////////////////////////////////////////////
      auto NodeRotationKeyframes(const aiScene *raw_model, std::string node_name) const
          -> std::vector<aiQuatKey>;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets all scaling keyframes for a certain node in a model.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @param[in] node_name Name of node.
      /// @return All scaling keyframes for the node.
      ////////////////////////////////////////////////////////////////////////////////
      auto NodeScalingKeyframes(const aiScene *raw_model, std::string node_name) const
          -> std::vector<aiVectorKey>;

     private:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets all position keyframes for all nodes in a model.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @return All position keyframes for the model.
      ////////////////////////////////////////////////////////////////////////////////
      auto AnimPositionKeyframes(const aiScene *raw_model) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets all rotation keyframes for all nodes in a model.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @return All rotation keyframes for the model.
      ////////////////////////////////////////////////////////////////////////////////
      auto AnimRotationKeyframes(const aiScene *raw_model) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets all scaling keyframes for all nodes in a model.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @return All scaling keyframes for the model.
      ////////////////////////////////////////////////////////////////////////////////
      auto AnimScalingKeyframes(const aiScene *raw_model) const;
   };
}

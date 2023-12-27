#pragma once

namespace Narradia
{
    // Show sub classes 
#if 1
   class Keyframe
   {
     public:
      std::vector<Vertex3F> vertices;
   };

   class Timeline
   {
     public:
      std::map<float, std::shared_ptr<const Keyframe>> keyframes;
   };

   class ModelPart
   {
     public:
      ModelPart()
          : timeline_(std::make_shared<Timeline>())
      {
      }

      auto texture_name()
      {
         return texture_name_;
      }

      void set_texture_name(std::string value)
      {
         texture_name_ = value;
      }

      auto timeline()
      {
         return timeline_;
      }

     private:
      std::string texture_name_;
      std::shared_ptr<Timeline> timeline_;
   };
#endif

   class Model
   {
     public:
      Model(int anim_duration)
          : anim_duration_(anim_duration),
            model_parts_(std::make_shared<std::vector<std::shared_ptr<ModelPart>>>())
      {
      }

      auto anim_duration()
      {
         return anim_duration_;
      }

      auto model_parts()
      {
         return model_parts_;
      }

     private:
      const int anim_duration_;
      std::shared_ptr<std::vector<std::shared_ptr<ModelPart>>> model_parts_;
   };
}

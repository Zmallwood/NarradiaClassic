#pragma once
namespace Narradia
{
   namespace ObjectFlags
   {
      static constexpr int None = 0;
      static constexpr int NoObstacle = 1 << 0;
   }

   class ObjectConfEntry
   {
     public:
      int flags = 0;
      float model_scaling = 1.0f;
   };

   class ObjectsConf : public Singleton<ObjectsConf>
   {
     public:
      ObjectsConf();
      auto IsObstacle(std::string_view object_type) -> bool;
      auto GetModelScaling(std::string_view object_type) -> float;

     private:
      std::map<std::string_view, ObjectConfEntry> object_confs_;
   };
}

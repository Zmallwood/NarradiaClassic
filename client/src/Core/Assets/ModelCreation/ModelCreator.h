#pragma once

namespace Narradia {
   class Model;

   class ModelCreator : public Singleton<ModelCreator> {
     public:
      auto CreateModel(const aiScene *_rawModel) -> SharedPtr<Model>;

     private:
      auto ModelParts(const aiScene *_rawModel);
   };
}

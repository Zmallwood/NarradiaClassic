#pragma once

namespace Narradia
{
   class Model;

   class ModelConstr : public S<ModelConstr>
   {
     public:
      auto CreateModel(const aiScene *raw_model) -> std::shared_ptr<Model>;

     private:
      auto ModelParts(const aiScene *raw_model);
   };
}
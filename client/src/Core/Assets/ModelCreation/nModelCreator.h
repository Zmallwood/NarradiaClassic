#pragma once

namespace Narradia {
   class nModel;

   class nModelCreator : public Singleton<nModelCreator> {
     public:
      auto CreateModel(const aiScene *_rawModel) -> SharedPtr<nModel>;

     private:
      auto ModelParts(const aiScene *_rawModel);
   };
}

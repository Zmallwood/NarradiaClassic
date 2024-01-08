#pragma once

namespace Narradia {
   class ImageBank : public Singleton<ImageBank> {
     public:
      ImageBank();
      ~ImageBank();
      GLuint GetImage(StringView _imgName);
      void CreateBlankTextImage(String _uniqueImgName);

     private:
      void LoadImages();
      GLuint LoadSingleImage(StringView _absFilePath);

      const StringView k_relImagesPath = "Resources/Images/";
      Map<String, GLuint> m_images;
   };
}

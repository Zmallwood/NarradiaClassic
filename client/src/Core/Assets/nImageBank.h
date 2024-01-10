#pragma once

namespace Narradia {
   class nImageBank : public Singleton<nImageBank> {
     public:
      nImageBank();
      ~nImageBank();
      GLuint GetImage(StringView _imgName);
      void CreateBlankTextImage(String _uniqueImgName);

     private:
      void LoadImages();
      GLuint LoadSingleImage(StringView _absFilePath);

      const StringView k_relImagesPath = "Resources/Images/";
      Map<String, GLuint> m_images;
   };
}

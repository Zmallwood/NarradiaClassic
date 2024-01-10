#include "nImageBank.h"
#include "Conf/Constants.h"

namespace Narradia {
   nImageBank::nImageBank() {
      LoadImages();
   }

   nImageBank::~nImageBank() {
      if (k_verbose)
         std::cout << "Cleaning up ImageBank\n";
      for (const auto &_img : m_images)
         glDeleteTextures(1, &_img.second);
      if (k_verbose)
         std::cout << "Cleaning up of ImageBank finished.\n";
   }

   GLuint nImageBank::GetImage(StringView _imgName) {
      for (auto _img : m_images)
         if (_img.first == _imgName)
            return _img.second;
      return -1;
   }

   void nImageBank::CreateBlankTextImage(String _uniqueImgName) {
      GLuint __texId;
      glGenTextures(1, &__texId);
      m_images.insert({_uniqueImgName, __texId});
   }

   void nImageBank::LoadImages() {
      using iterator = std::filesystem::recursive_directory_iterator;
      auto _allImagesPath = String(SDL_GetBasePath()) + k_relImagesPath.data();
      for (auto &_entry : iterator(_allImagesPath)) {
         auto _absPath = _entry.path().string();
         if (FileExtension(_absPath) != "png")
            continue;
         auto _texId = LoadSingleImage(_absPath);
         auto _imgName = FileNameNoExt(_absPath);
         m_images[_imgName] = _texId;
      }
   }

   GLuint nImageBank::LoadSingleImage(StringView _absFilePath) {
      GLuint _texId;
      auto _surf = IMG_Load(_absFilePath.data());
      glEnable(GL_TEXTURE_2D);
      glGenTextures(1, &_texId);
      glBindTexture(GL_TEXTURE_2D, _texId);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      // clang-format off
      if (_surf->format->BytesPerPixel == 4) {
         glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA,
            _surf->w,
            _surf->h,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            _surf->pixels);
      } else {
         glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            _surf->w,
            _surf->h,
            0, GL_RGB,
            GL_UNSIGNED_BYTE,
            _surf->pixels);
      }
      // clang-format on
      SDL_FreeSurface(_surf);
      return _texId;
   }
}

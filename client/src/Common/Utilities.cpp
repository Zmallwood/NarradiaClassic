#include "Utilities.h"
#include "Core/Assets/ImageBank.h"

namespace Narradia {
   PointF MousePos() {
      int _xPx, _yPx;
      auto _canvSz = CanvasSize();
      SDL_GetMouseState(&_xPx, &_yPx);
      auto _x = static_cast<float>(_xPx) / _canvSz.w;
      auto _y = static_cast<float>(_yPx) / _canvSz.h;
      return {_x, _y};
   }
   StringView CurrTime() {
      char _buffer[80];
      auto _now = time(0);
      auto _pTStruct = localtime(&_now);
      strftime(_buffer, sizeof(_buffer), "%X", _pTStruct);
      return StringView(_buffer);
   }
   Size TexDimensions(StringView _imgName) {
      Size _dim;
      int _mipLevel = 0;
      auto _imgID = ImageBank::get()->GetImage(_imgName);
      glBindTexture(GL_TEXTURE_2D, _imgID);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, _mipLevel, GL_TEXTURE_WIDTH, &_dim.w);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, _mipLevel, GL_TEXTURE_HEIGHT, &_dim.h);
      return _dim;
   }
}

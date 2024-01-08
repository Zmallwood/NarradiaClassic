#pragma once

namespace Narradia {
   template <class T>
   class Square {
     public:
      void SetAll(T _value) {
         _00 = _value;
         _01 = _value;
         _11 = _value;
         _10 = _value;
      }

      T _00;
      T _01;
      T _11;
      T _10;
   };
}

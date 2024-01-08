#pragma once

namespace Narradia {

    template <class T>
    class Square {

      public:
        void SetAll(T value) {

            _00 = value;
            _01 = value;
            _11 = value;
            _10 = value;
        }

        T _00;
        T _01;
        T _11;
        T _10;
    };
}

#pragma once

namespace Narradia {
    class Point3F {
      public:
        Point3F Translate(float dx, float dy, float dz);

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };
}

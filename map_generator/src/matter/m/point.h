#pragma once
namespace Narradia
{
    /**
     Integer type 2D point.
    */
    class Point {
      public:
        Point Translate(int dx, int dy);

        int x = 0;
        int y = 0;
    };
}

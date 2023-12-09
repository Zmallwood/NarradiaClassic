#include "Point.h"

namespace Narradia
{
    Point Point::Translate(int dx, int dy) { return {x + dx, y + dy}; }
}

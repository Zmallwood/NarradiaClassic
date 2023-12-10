#include "trigonometry.h"

namespace Narradia {
  float SinDeg(float angle_deg) {
    return sinf(angle_deg * static_cast<float>(M_PI) / 180.0f);
  }

  float CosDeg(float angle_deg) {
    return cosf(angle_deg * static_cast<float>(M_PI) / 180.0f);
  }
}

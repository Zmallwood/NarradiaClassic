#pragma once

#include "WorldStructure/WorldStructure.h"
#include "Conf/Constants.h"

namespace Narradia {

   // Trigonometry

#if 1
   inline float SinDeg(float angle_deg) {
      return sinf(angle_deg * static_cast<float>(M_PI) / 180.0f);
   }

   inline float CosDeg(float angle_deg) {
      return cosf(angle_deg * static_cast<float>(M_PI) / 180.0f);
   }
#endif

   // Tile calculations

#if 1
   inline float CalcTileAverageElevation(Point coord, Point world_loc) {
      auto map_area = World::get()->WorldAreaAt({world_loc.x, world_loc.y});

      auto elev00 = map_area->GetTile(coord.x, coord.y)->elevation() * k_elevAmount;
      auto elev10 = elev00;
      auto elev11 = elev00;
      auto elev01 = elev00;

      auto coord10 = Point{coord.x + 1, coord.y};
      auto coord11 = Point{coord.x + 1, coord.y + 1};
      auto coord01 = Point{coord.x, coord.y + 1};

      if (map_area->IsInsideMap(coord10))
         elev10 = map_area->GetTile(coord10)->elevation() * k_elevAmount;

      if (map_area->IsInsideMap(coord11))
         elev11 = map_area->GetTile(coord11)->elevation() * k_elevAmount;

      if (map_area->IsInsideMap(coord01))
         elev01 = map_area->GetTile(coord01)->elevation() * k_elevAmount;

      return (elev00 + elev10 + elev11 + elev01) / 4.0f;
   }

   inline Point3F CalcTileNormal(Point3F v0, Point3F v1, Point3F v2) {
      auto point0 = glm::vec3(v0.x, v0.y, v0.z);
      auto point1 = glm::vec3(v1.x, v1.y, v1.z);
      auto Point2 = glm::vec3(v2.x, v2.y, v2.z);

      auto vector0 = point1 - point0;
      auto vector1 = Point2 - point0;
      auto vector2 = glm::cross(vector0, vector1);

      auto normal_gl = glm::normalize(vector2);

      return {-normal_gl.x, -normal_gl.y - normal_gl.z};
   }
#endif

   // Exp calculations

#if 1
   inline int GetCurrentLevel(int exp) {
      auto value = std::trunc(log2f(pow(exp + 70, 2) / 5000)) + 1;
      auto level = static_cast<int>(value);

      return level;
   }

   inline int GetExpForLevel(int lvl) {
      auto value = std::max(sqrtf(powf(2, lvl - 1) * 5000) - 70, 0.0f);
      auto experience = static_cast<int>(value);

      return experience;
   }

   inline int GetExpDiffToNextLevel(int exp) {
      auto current_level = GetCurrentLevel(exp);
      auto next_level = current_level + 1;

      auto total_experience_current_level = GetExpForLevel(current_level);
      auto total_experience_next_level = GetExpForLevel(next_level);

      auto experience_difference = total_experience_next_level - total_experience_current_level;

      return experience_difference;
   }

   inline int GetExpReqForCurrLevelStart(int exp) {
      auto current_level = GetCurrentLevel(exp);
      auto total_experience_current_level_start = GetExpForLevel(current_level);

      return total_experience_current_level_start;
   }

   inline int GetExpGainedSinceLevelStart(int exp) {
      auto experience_since_start = exp - GetExpReqForCurrLevelStart(exp);

      return experience_since_start;
   }

   inline float GetFractionalExpProgress(int exp) {
      auto experience_gain = exp - GetExpReqForCurrLevelStart(exp);
      auto experience_difference = GetExpDiffToNextLevel(exp);
      auto progress_fractional = static_cast<float>(experience_gain) / experience_difference;

      return progress_fractional;
   }
#endif

}

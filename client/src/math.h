#pragma once

#include "matter.h"

namespace Narradia
{
    // Trigonometry
   float SinDeg(float angle_deg);
   float CosDeg(float angle_deg);

   // Tile calculations
   float CalcTileAverageElevation(Point coord);
   Point3F CalcTileNormal(Point3F v0, Point3F v1, Point3F v2);

   // Exp calculations
   int GetCurrentLevel(int exp);
   int GetExpForLevel(int lvl);
   int GetExpDiffToNextLevel(int exp);
   int GetExpReqForCurrLevelStart(int exp);
   int GetExpGainedSinceLevelStart(int exp);
   float GetFractionalExpProgress(int exp);
}

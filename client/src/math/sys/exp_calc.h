#pragma once
namespace Narradia
{
   int GetCurrentLevel(int exp);
   int GetExpForLevel(int lvl);
   int GetExpDiffToNextLevel(int exp);
   int GetExpReqForCurrLevelStart(int exp);
   int GetExpGainedSinceLevelStart(int exp);
   float GetFractionalExpProgress(int exp);
}

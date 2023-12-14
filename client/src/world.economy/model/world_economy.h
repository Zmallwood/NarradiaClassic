#pragma once
#include "money_bank.h"
namespace Narradia
{
   class WorldEconomy : public Singleton<WorldEconomy> {
     public:
     private:
      std::vector<MoneyBank> banks_;
   };
}

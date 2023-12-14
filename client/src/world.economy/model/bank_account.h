#pragma once
namespace Narradia
{
   class BankAccount {
     public:
      auto saldo() {
         return saldo_;
      }

     private:
      int saldo_ = 0;
   };
}

#pragma once

#include "core.h"

namespace Narradia
{
   class IntroPg : public IPage, public S<IntroPg> {
     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override {
      }
   };

   class MainMenuPg : public IPage, public S<MainMenuPg> {
     public:
      MainMenuPg();

     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override {
      }
   };

   class MapCreationPg : public IPage, public S<MapCreationPg> {
     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override;
   };

   class MainPg : public IPage, public S<MainPg> {
     public:
      MainPg();

     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override {
      }
   };
}

#pragma once

#include "core_c.h"

namespace Narradia
{
   class IntroPgC : public IPageC, public S<IntroPgC> {
     private:
      void OnEnter() override;
      void UpdateGameFlowDerived() override;
   };

   class MainMenuPgC : public IPageC, public S<MainMenuPgC> {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };

   class MapCreationPgC : public IPageC, public S<MapCreationPgC> {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };

   class MainPgC : public IPageC, public S<MainPgC> {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };
}


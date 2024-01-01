#pragma once

#include "core.h"

namespace Narradia
{
   // Model
#if 1
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
#endif

// View
#if 1
   class IntroPgV : public IPageV, public S<IntroPgV> {
     public:
      IntroPgV();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
      RenderID rid_text;
   };

   class MainMenuPgV : public IPageV, public S<MainMenuPgV> {
     public:
      MainMenuPgV();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
   };

   class MapCreationPgV : public IPageV, public S<MapCreationPgV> {
     private:
      void RenderDerived() override;
   };

   class MainPgV : public IPageV, public S<MainPgV> {
     public:
      MainPgV();

     private:
      void RenderDerived() override;
   };

#endif

   // Controller
#if 1
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
#endif
}

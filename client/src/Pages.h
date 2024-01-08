#pragma once

#include "Engine/Core.h"

namespace Narradia {

   // Model

#if 1
   class IntroPg : public IPage, public Singleton<IntroPg> {
     private:
      void UpdateGameLogicDerived() override;

      void Finalize() override {
      }
   };

   class MainMenuPg : public IPage, public Singleton<MainMenuPg> {
     public:
      MainMenuPg();

     private:
      void UpdateGameLogicDerived() override;

      void Finalize() override {
      }
   };

   class MapCreationPg : public IPage, public Singleton<MapCreationPg> {
     private:
      void UpdateGameLogicDerived() override;
      void Finalize() override;
   };

   class MainPg : public IPage, public Singleton<MainPg> {
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
   class IntroPgV : public IPageV, public Singleton<IntroPgV> {
     public:
      IntroPgV();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
      RenderID rid_text;
   };

   class MainMenuPgV : public IPageV, public Singleton<MainMenuPgV> {
     public:
      MainMenuPgV();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
   };

   class MapCreationPgV : public IPageV, public Singleton<MapCreationPgV> {
     private:
      void RenderDerived() override;
   };

   class MainPgV : public IPageV, public Singleton<MainPgV> {
     public:
      MainPgV();

     private:
      void RenderDerived() override;
   };

#endif

   // Controller

#if 1
   class IntroPgC : public IPageC, public Singleton<IntroPgC> {
     private:
      void OnEnter() override;
      void UpdateGameFlowDerived() override;
   };

   class MainMenuPgC : public IPageC, public Singleton<MainMenuPgC> {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };

   class MapCreationPgC : public IPageC, public Singleton<MapCreationPgC> {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };

   class MainPgC : public IPageC, public Singleton<MainPgC> {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };
#endif

}

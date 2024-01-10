#pragma once

#include "Core/Core.h"

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
   class IntroPgView : public IPageView, public Singleton<IntroPgView> {
     public:
      IntroPgView();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
      RenderID rid_text;
   };

   class MainMenuPgView : public IPageView, public Singleton<MainMenuPgView> {
     public:
      MainMenuPgView();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
   };

   class MapCreationPgView : public IPageView, public Singleton<MapCreationPgView> {
     private:
      void RenderDerived() override;
   };

   class MainPgView : public IPageView, public Singleton<MainPgView> {
     public:
      MainPgView();

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

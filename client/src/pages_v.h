#pragma once

#include "core_v.h"

namespace Narradia
{
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
}


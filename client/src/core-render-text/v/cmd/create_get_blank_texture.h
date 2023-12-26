#pragma once
#include "core-assets/m/image_bank.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Creates and returns unique name for a new blank texture.
   ///
   /// @return Unique name for the newly created blank texture.
   ////////////////////////////////////////////////////////////////////////////////
   auto CreateGetBlankTexture() -> std::string;
}

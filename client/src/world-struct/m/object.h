#pragma once
namespace Narradia
{
   class Object
   {
     public:
      Object(std::string type);

      auto type()
      {
         return type_;
      }

      void set_type(std::string_view value)
      {
         type_ = value;
      }

     private:
      std::string type_ = "";
   };
}

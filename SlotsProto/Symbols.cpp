#include "Symbols.h"
#include <string>

std::string symbolToString(const symbol& symbol) {
   switch (symbol)
   {
   case(symbol::Apple):
      return "APP";
      break;
   case(symbol::Banana):
      return "Ban";
      break;
   case(symbol::Cherry):
      return "CHE";
      break;
   case(symbol::Grape):
      return "GRA";
      break;
   case(symbol::Kiwi):
      return "KIW";
      break;
   case(symbol::Lime):
      return "LIM";
      break;
   case(symbol::Mango):
      return "MAN";
      break;
   case(symbol::Orange):
      return "ORA";
      break;
   case(symbol::Peach):
      return "PEA";
      break;
   case(symbol::Pineapple):
      return "PIN";
      break;
   default:
      return "INVALID SYMBOL";
      break;
   }
}
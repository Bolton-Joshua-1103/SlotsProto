#include "SymbolCombination.h"

SymbolCombination::SymbolCombination()
{
}

SymbolCombination::SymbolCombination(std::initializer_list<int> args) {
   for (const auto& ele : args) {
      symbols.push_back(symbol(ele));
   }
}

SymbolCombination::SymbolCombination(std::initializer_list<symbol> args) {
   for (const auto& ele : args) {
      symbols.push_back(ele);
   }
}

bool SymbolCombination::operator <(const SymbolCombination& rhs) const{
   if (rhs.symbols.size() < symbols.size()) {
      return false;
   }
   else if (rhs.symbols.size() > symbols.size()) return true;

   //They are the same length if we made it here
   for (int index{ 0 }; index < symbols.size(); index++) {
      if (rhs.symbols[index] < symbols[index]) return true;
      else if (rhs.symbols[index] > symbols[index]) return false;
   }
   return false;
}
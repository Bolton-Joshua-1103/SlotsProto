#pragma once
#include "Symbols.h"
#include <vector>
class SymbolCombination
{
public:
   SymbolCombination();
   std::vector<symbol> symbols;
   bool operator <(const SymbolCombination&) const;
private:

};


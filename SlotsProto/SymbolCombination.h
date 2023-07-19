#pragma once
#include "Symbols.h"
#include <vector>
class SymbolCombination
{
public:
   SymbolCombination();
   std::vector<symbol> symbols;
   bool operator <(const SymbolCombination&) const;
   inline bool isActive() const { return active_payline; }
   inline void setActive(bool val) { active_payline = val; }

private:
   bool active_payline = false; //This determines if this is an active payline
};


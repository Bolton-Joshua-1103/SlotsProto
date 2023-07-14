#include "CombinationEvaluator.h"
#include "SymbolCombination.h"
#include "Symbols.h"
#include <utility>
#include <iostream>

CombinationEvaluator::CombinationEvaluator()
{
   //Maybe delegate to the parameterized ctor with maxSymbols?
}

CombinationEvaluator::CombinationEvaluator(int reelcount)
{
   //Maybe check if it's possible to generate all possible combinations...
   // Maybe only load with winning combos?.... interesting
   for (unsigned int symbolInt = 0; symbolInt < unique_symbol_count; symbolInt++) {
      SymbolCombination jackPotCombo{};
      for (int reelIndex{ 0 }; reelIndex < reelcount; reelIndex++) {
         jackPotCombo.symbols.push_back(static_cast<symbol>(symbolInt));//Creates SymbolCombinations of all the same symbols according to the number of the reels
      }
      evalmap.insert({ jackPotCombo, 100 });
   }
}

size_t CombinationEvaluator::checkPayLineCombinations(const std::vector<SymbolCombination>& payLineCombos)
{
   size_t jackpot_running_total = { 0 };
   for (const auto& symbol_combination : payLineCombos) {
      auto combo_map_it = evalmap.find(symbol_combination);
      if (combo_map_it != evalmap.end()) {
         jackpot_running_total += combo_map_it->second;
      }
   }
   return jackpot_running_total;
}


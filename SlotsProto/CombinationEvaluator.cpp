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
      int jackPotAmount = pow(10, reelcount - 1); //This creates a 100% PBR, using for testing. This evaluator should probably be populated from a file.
      evalmap.insert({ jackPotCombo, jackPotAmount });
   }
}

size_t CombinationEvaluator::checkPayLineCombinations(const std::vector<SymbolCombination>& payLineCombos)
{
   size_t jackpot_running_total = { 0 };
   for (const auto& symbol_combination : payLineCombos) {
      if (symbol_combination.isActive()) {
         auto combo_map_it = evalmap.find(symbol_combination);
         if (combo_map_it != evalmap.end()) {

            jackpot_running_total += combo_map_it->second;
         }
      }
   }
   return jackpot_running_total;
}


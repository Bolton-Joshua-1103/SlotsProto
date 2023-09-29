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
      int jackPotAmount = pow(10, reelcount - 1) /2;
      evalmap.insert({ jackPotCombo, jackPotAmount });
   }



   // Adding two of a kind support: There are 270 combos out of 1000 total combos (assumed 3 reels right now)
   // THis means that ther eis a 270/1000 chance of hitting the two of a kind and you need to pay back 1000/270*betprice for 100% paayback rate
   for (int symbol_pair = 0; symbol_pair < 10; ++symbol_pair) {
      for (int lone_symbol = 0; lone_symbol < 10; ++lone_symbol) {
         if (lone_symbol != symbol_pair) {
            evalmap.insert({ { symbol_pair, symbol_pair, lone_symbol }, (double)500 / 270});
            evalmap.insert({ { symbol_pair, lone_symbol, symbol_pair }, (double)500 / 270 });
            evalmap.insert({ { lone_symbol, symbol_pair,  symbol_pair }, (double)500 / 270 });
         }
      }
   }
   auto test_var = evalmap.size();
   
}

double CombinationEvaluator::checkPayLineCombinations(const std::vector<SymbolCombination>& payLineCombos)
{
   double jackpot_running_total = { 0 };
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


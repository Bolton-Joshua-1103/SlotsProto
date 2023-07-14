#pragma once
#include <map>
#include "SymbolCombination.h"
class CombinationEvaluator
{
public:
   CombinationEvaluator();
   CombinationEvaluator(int);
   size_t checkPayLineCombinations(const std::vector<SymbolCombination>&);
private:
   std::map<SymbolCombination, int> evalmap; //Should change bool to int/double(amount you would win)
};


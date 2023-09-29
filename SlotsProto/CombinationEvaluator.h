#pragma once
#include <map>
#include "SymbolCombination.h"
class CombinationEvaluator
{
public:
   CombinationEvaluator();
   CombinationEvaluator(int);
   double checkPayLineCombinations(const std::vector<SymbolCombination>&);
private:
   std::map<SymbolCombination, double> evalmap; //Should change bool to int/double(amount you would win)
};


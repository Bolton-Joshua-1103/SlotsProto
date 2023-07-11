#pragma once
#include <vector>
#include "Symbols.h"
class Reel
{
public:
   Reel();
   Reel(int);
   const std::vector<symbol>& getStrip() const {
      return strip;
   };
   
private:
   static constexpr int default_number_stops = 10;
   std::vector<symbol> strip;
};


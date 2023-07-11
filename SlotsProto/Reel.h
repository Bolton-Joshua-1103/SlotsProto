#pragma once
#include <vector>
class Reel
{
public:
   Reel();
   Reel(int);
   const std::vector<int>& getStrip() const {
      return strip;
   };
   
private:
   static constexpr int default_number_stops = 10;
   std::vector<int> strip;
};


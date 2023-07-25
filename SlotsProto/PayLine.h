#pragma once
#include <functional>
#include <vector>
class PayLine
{
public:
   PayLine();
   PayLine(std::function<int(int)>,  size_t, const size_t&);
   const std::vector<int>& getIndicies() const;
   size_t size() const;
   inline bool isActive()  const {return active_payline; }
   inline void setActive(bool val)  {active_payline = val; }
private:
   std::vector<int> indicies;
   bool active_payline = false;
};


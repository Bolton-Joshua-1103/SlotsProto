#pragma once
#include <functional>
#include <vector>
class PayLine
{

   /*
   What is a pay line: A payline is a specific set of indices that reference certain
   positions in the paywindow.

   What does a payline do: A payline checks ReelViews for "winning" combinations in their
   specific positions.

   How should you use a payline? A payline should take a ReelView and check it's positions
   for winning combinations. For now maybe we should just do a true/false for a winning combination

   foreach(Paylines in collection){
      payline.evaluate();
   }
   */
public:
   PayLine();
   PayLine(std::function<int(int)>,  size_t, const size_t&);
   const std::vector<int>& getIndicies() const;
   size_t size() const;
private:
   std::vector<int> indicies;
};


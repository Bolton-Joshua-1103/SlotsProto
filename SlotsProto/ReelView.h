#pragma once
#include <vector>
#include "Reel.h"
#include "PayLine.h"
#include "Symbols.h"
class ReelView
{
public:
   ReelView();
   ReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops);//In order to print anything out you need to know about the reels and the reel stops.
   void printReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops);
   void updateReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops);
private:
   void populateReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops);
   void populatePayLines(const std::vector<Reel>& reels);

   // START HERE WHEN YOU GET BACK
   void EvaluatePayLines();//Uses the ReelView and the PayLines collection to see if there are any wins
   void printPayLineIndices();
   std::vector<std::vector<symbol>> viewingVector;
   std::vector<PayLine> payLines;

};


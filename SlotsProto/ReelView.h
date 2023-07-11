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

   void printPayLineCombos() const;

private:
   void populateReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops);
   
   void populatePayLines();
   void printPayLineIndices();

   void populatePayLineCombos();
   void updatePayLineCombos();


   std::vector<std::vector<symbol>> viewingVector;
   std::vector<PayLine> payLines;
   std::vector<std::vector<symbol>> payLineCombos; //Reads symbols on paylines to generate combinations of symbols to check for winning combos

};


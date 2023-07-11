#pragma once
#include <vector>
#include "Reel.h"
#include "ReelView.h"

class SlotMachine
{
public:
   SlotMachine();
   SlotMachine(int);

   void printViewingWindow();
   void spinReels();

private:

   static constexpr int DefaultReelCount = 3;
   std::vector<Reel> reels;
   std::vector<unsigned int> reelStops;
   ReelView reelview;


   void printReelInfo();
};


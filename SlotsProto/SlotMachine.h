#pragma once
#include <vector>
#include "Reel.h"
#include "ReelView.h"
#include "CombinationEvaluator.h"
#include "NumericalConfigurator.h"
#include "CreditStateTracker.h"

class SlotMachine
{
public:
   SlotMachine();
   SlotMachine(int);

   void printViewingWindow();
   void spinReels();
   void checkWin();
   void playRound();

private:

   static constexpr int DefaultReelCount = 3;
   std::vector<Reel> reels;
   std::vector<unsigned int> reelStops;


   ReelView reelview;
   CombinationEvaluator evaluator;
   NumericalConfigurator configuration;
   CreditStateTracker tracker;

   void printReelInfo();
};


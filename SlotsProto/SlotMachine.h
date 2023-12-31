#pragma once
#include <vector>
#include <string>
#include "Reel.h"
#include "ReelView.h"
#include "CombinationEvaluator.h"
#include "NumericalConfigurator.h"
#include "CreditStateTracker.h"

class SlotMachine
{
public:
   SlotMachine();
   SlotMachine(const std::string);
   SlotMachine(const int);
   SlotMachine(const int, const std::string);
   SlotMachine(const int, const std::string, const std::string&, const bool);

   void printViewingWindow();
   void playRound(const char&);

private:

   static constexpr int DefaultReelCount = 3;
   std::vector<Reel> reels;
   std::vector<unsigned int> reelStops;
   bool verbose = true;

   ReelView reelview;
   CombinationEvaluator evaluator;
   NumericalConfigurator configuration;
   CreditStateTracker tracker;

   void spinReels();
   void checkWin();
   void printReelInfo(); //Prints reel contents to console. Assumes uniform reel size
};


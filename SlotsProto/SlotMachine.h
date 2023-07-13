#pragma once
#include <vector>
#include "Reel.h"
#include "ReelView.h"
#include "CombinationEvaluator.h"

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
   static constexpr int Default_Price_Per_PayLine = 1;
   static constexpr int Default_Starting_Credits = 3;
   std::vector<Reel> reels;
   std::vector<unsigned int> reelStops;
   ReelView reelview;
   CombinationEvaluator evaluator;

   int credits_used{ 0 };
   int credits_won{ 0 };
   double pay_back_rate{ 0 };

   int price_per_payline;
   int credits;


   void printReelInfo();
   void upDatePayPackRate();
};


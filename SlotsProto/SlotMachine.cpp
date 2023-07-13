#include "SlotMachine.h"
#include <iostream>
#include <random>

SlotMachine::SlotMachine() : SlotMachine::SlotMachine(DefaultReelCount) {}


SlotMachine::SlotMachine(int total_reels) : price_per_payline(Default_Price_Per_PayLine), credits(Default_Starting_Credits) {
   for (int reelindex = 0; reelindex < total_reels; reelindex++) {
      reels.push_back(Reel{});
      reelStops.push_back(0);
   }
   reelview = ReelView(reels, reelStops); //I keep doing this. is this okay?
   //printReelInfo(); //For debugging purposes
   evaluator = CombinationEvaluator(total_reels);
} 

void SlotMachine::printViewingWindow()
{
   std::cout << "---CURRENT VIEWING WINDOW---" << std::endl;
   reelview.printReelView(reels, reelStops);
   std::cout << "---END VIEWING WINDOW---" << std::endl;
   std::cout << "AVAILABLE CREDITS: " << credits << std::endl;
   std::cout << "Current PayBackRate: " << pay_back_rate << std::endl;
   //reelview.printPayLineCombos();

}

void SlotMachine::spinReels()
{
   /*
   * DETERMINISTIC METHOD - CAN BE USED FOR DEBUGGING AND REPRODUCABILITY
   std::default_random_engine generator;
   std::uniform_int_distribution<int> distribution(0, 9);
   */

   //NonDeterministic Method being used below
   std::random_device rd;
   std::mt19937 generator(rd());
   std::uniform_int_distribution<int> distribution(0, 9);

   for (unsigned int reel_index{ 0 }; reel_index < reels.size(); ++reel_index) {
      reelStops[reel_index] = distribution(generator);
   }
}

void SlotMachine::checkWin()
{
   int jackpot_total = evaluator.checkPayLineCombinations(reelview.getPayLineCombos());
   if (jackpot_total > 0) {
      credits += jackpot_total;
      credits_won += jackpot_total;
   }
}

void SlotMachine::playRound()
{
   //Give them 3 credits to start. Each bet will be 3 credits. 1 credits on each payline
   //The math should be a 1:100 chance of winning as there are 1 jackpots each with a 1/1000 chance
   //To start this means that each jackpot should pay back 103 credits. This should be 100% payback?
   // This is what I need to test next.
   int cost = price_per_payline * reelview.getPayLineCombos().size();
   credits -= cost;
   credits_used += cost;

   spinReels();
   printViewingWindow();
   checkWin();
   upDatePayPackRate();
}

void SlotMachine::printReelInfo()
{
   for ( auto & reel : reels) {
      std::cout << "REEL: ";
      for (const auto& symbol : reel.getStrip()) {
         std::cout << symbolToString(symbol) << " ";
      }
      std::cout << std::endl;
   }
}

void SlotMachine::upDatePayPackRate()
{
   pay_back_rate = credits_won / credits_used;
}

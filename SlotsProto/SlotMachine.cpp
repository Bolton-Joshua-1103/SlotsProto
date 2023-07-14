#include "SlotMachine.h"
#include <iostream>
#include <random>

SlotMachine::SlotMachine() : SlotMachine::SlotMachine(DefaultReelCount) {}


SlotMachine::SlotMachine(int total_reels) {
   for (int reelindex = 0; reelindex < total_reels; reelindex++) {
      reels.push_back(Reel{});
      reelStops.push_back(0);
   }
   reelview = ReelView(reels, reelStops); 
   evaluator = CombinationEvaluator(total_reels);
   configuration = NumericalConfigurator{};
   tracker = CreditStateTracker(configuration.get_starting_credits());
} 

void SlotMachine::printViewingWindow() {
   static int rounds_won_so_far = 0;
   std::cout << "---CURRENT VIEWING WINDOW---" << std::endl;
   reelview.printReelView(reels, reelStops);
   std::cout << "---END VIEWING WINDOW---" << std::endl;
   std::cout << "AVAILABLE CREDITS: " << tracker.getCredits() << std::endl;
   
   std::cout << "Credits Spent: " << tracker.getCreditsUsed() << std::endl;
   std::cout << "Credits Won: " << tracker.getCreditsWon() << std::endl;
   std::cout << "Rounds Played: " << tracker.getRoundsPlayed() << std::endl;
   std::cout << "Rounds Won: " << tracker.getRoundsWon() << std::endl;

   std::cout << "Current PayBackRate: " << tracker.getPayBackRate() << std::endl;
   std::cout << "Current HitRate: " << tracker.getHitRate() << std::endl;
   reelview.printPayLineCombos();
   if (rounds_won_so_far < tracker.getRoundsWon()) {
      std::cout << "\n \n \n YOU WON!!!! \n YOU WON!!!! \n YOU WON!!!!" << std::endl;
      rounds_won_so_far = tracker.getRoundsWon();
   }

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
   //This call below assumes you bet all paylines. Can change later (@@@)
   size_t jackpot_total = evaluator.checkPayLineCombinations(reelview.getPayLineCombos());
   if (jackpot_total > 0) {
      tracker.gameWon(jackpot_total);
   }
   
}

void SlotMachine::playRound()
{
   if (tracker.gamePlayed(configuration.get_cost_per_payline() * reelview.payLineCount())) {
      spinReels();
      reelview.updateReelView(reels, reelStops); //This updates the reelview with the newly spun reels
      checkWin();//Checks to see if new reel combination is winning and pays credits back
      tracker.updateGameStats(); //Updates teh game states after a round has been played and winning has been determined
      printViewingWindow(); //Prints out everything to window

   }

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


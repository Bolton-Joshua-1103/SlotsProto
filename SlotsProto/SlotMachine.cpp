#include "SlotMachine.h"
#include <iostream>
#include <random>

SlotMachine::SlotMachine() : SlotMachine::SlotMachine(DefaultReelCount, "Default") {}
SlotMachine::SlotMachine(std::string _slot_id) : SlotMachine::SlotMachine(DefaultReelCount, _slot_id) {}
SlotMachine::SlotMachine(int total_reels) : SlotMachine::SlotMachine(total_reels, "Default") {}

SlotMachine::SlotMachine(const int total_reels, const std::string _slot_id) 
   : evaluator{ total_reels }, tracker{configuration.get_starting_credits(), _slot_id} {
   //Loading reels with 0-9, can be changed
   for (int reelindex = 0; reelindex < total_reels; reelindex++) {
      reels.push_back(Reel{});
      reelStops.push_back(0);
   }
   reelview = ReelView{ reels, reelStops }; //Needs to be done after the reels are initialized (the for loop above)
   //Configurator is default constructed
} 


void SlotMachine::printViewingWindow() {
   static size_t rounds_won_so_far = 0;
   std::cout << "---CURRENT VIEWING WINDOW---" << std::endl;
   reelview.printReelView(reels, reelStops);
   std::cout << "---END VIEWING WINDOW---" << std::endl;
   tracker.printgameStats();
   reelview.printPayLineCombos();

   if (rounds_won_so_far < tracker.getRoundsWon()) {
      std::cout << "\n \n \n YOU WON!!!! \n YOU WON!!!! \n YOU WON!!!!" << std::endl;
      rounds_won_so_far = tracker.getRoundsWon();
   }

}

void SlotMachine::printInputMenu()
{
   std::cout << "PRESS 'q' TO QUIT" << std::endl;
   std::cout << "BET DESIRED NUMBER OF PAYLINES (defaulted to max bet with invalid input)" << std::endl;
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

void SlotMachine::playRound(const char& cmd)
{
   //Paylines are activated, game is played, paylines are deactivated
   int num_paylines_bet = reelview.validatePayLineNumInput(cmd);
   reelview.activatePayLines(num_paylines_bet);
   int total_bet_price = num_paylines_bet * configuration.get_cost_per_payline();

   if (tracker.gameRequested(total_bet_price)) {
      spinReels();
      reelview.updateReelView(reels, reelStops); //This updates the reelview with the newly spun reels
      checkWin();//Checks to see if new reel combination is winning and pays credits back
      tracker.updateGameStats(); //Updates teh game states after a round has been played and winning has been determined
      printViewingWindow(); //Prints out everything to window

   }
   reelview.deactivatePayLines(); // Needs to be called after a round has been played
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


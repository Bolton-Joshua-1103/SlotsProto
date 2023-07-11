#include "SlotMachine.h"
#include <iostream>
#include <random>

SlotMachine::SlotMachine() : SlotMachine::SlotMachine(DefaultReelCount) {}


SlotMachine::SlotMachine(int total_reels) {
   for (int reelindex = 0; reelindex < total_reels; reelindex++) {
      reels.push_back(Reel{});
      reelStops.push_back(0);
   }
   reelview = ReelView(reels, reelStops); //I keep doing this. is this okay?
   //printReelInfo();
} 

void SlotMachine::printViewingWindow()
{
   std::cout << "---CURRENT VIEWING WINDOW---" << std::endl;
   reelview.printReelView(reels, reelStops);
   std::cout << "---END VIEWING WINDOW---" << std::endl;
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

void SlotMachine::printReelInfo()
{
   for ( auto & reel : reels) {
      std::cout << "REEL: ";
      for (const auto& symbol : reel.getStrip()) {
         std::cout << symbol << " ";
      }
      std::cout << std::endl;
   }
}
#include "ReelView.h"
#include <iostream>

ReelView::ReelView() {
   //This should probably never be called. You need a reel and reel stop info to know what to do
}

ReelView::ReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops) {
   populateReelView(reels, reelStops);
   populatePayLines(reels);
   
}

void ReelView::populateReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops) {
   for (unsigned int row_index{ 0 }; row_index < reels.size(); ++row_index) {
      viewingVector.push_back(std::vector<int>{});//This creates a vector for each row
      for (unsigned int reel_index{ 0 }; reel_index < reels.size(); ++reel_index) {
         const auto& current_strip = reels[reel_index].getStrip();
         const auto& strip_stop = (reelStops[reel_index] + row_index) % current_strip.size(); //row_index increments the stop based on the row
         viewingVector[row_index].push_back(current_strip[strip_stop]);
      }
   }
}
void ReelView::populatePayLines(const std::vector<Reel>& reels)
{
   /*Here we need to create paylines - each will be different so we need to make them one at a time
      We still are trying to have a 'general' slot machine. So we need to make paylines relative to the
      size of reels.
   */
   payLines.push_back(PayLine{ [](int starting_index) {return starting_index; }, (reels.size()/2) ,reels.size()});// "Middle Payline"
   payLines.push_back(PayLine{ [](int starting_index) {static int increment = 0;  return starting_index + increment++; }, 0,reels.size() }); //Upper left to Lower right
   payLines.push_back(PayLine{ [](int starting_index) {static int increment = 0;  return starting_index + increment--; }, reels.size() -1, reels.size()}); //LowerLeft to Upper RIght
   printPayLineIndices(); //For debugging to see each payline index
}

void ReelView::printPayLineIndices()
{
   std::cout << "CHECKING PAYLINES: " << std::endl;
   for (auto& payline : payLines) {
      std::cout << "INDICIES: ";
      for (int index_ref{ 0 }; index_ref < payline.size(); ++index_ref) {
         std::cout << payline.getIndicies()[index_ref] << " ";
      }
      std::cout << std::endl;
   }
}



void ReelView::updateReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops) {
   for (unsigned int row_index{ 0 }; row_index < reels.size(); ++row_index) {
      for (unsigned int reel_index{ 0 }; reel_index < reels.size(); ++reel_index) {
         const auto& current_strip = reels[reel_index].getStrip();
         const auto& strip_stop = (reelStops[reel_index] + row_index) % current_strip.size(); //row_index increments the stop based on the row
         viewingVector[row_index][reel_index] = current_strip[strip_stop];
      }
   }
}

void ReelView::printReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops)
{
   //Always prints a square viewing window rows=#ofreels
   updateReelView(reels, reelStops); //Maybe have a flag to see if we need to do this. If nothing has changed (like no one has pulled the lever, then this in not necessary)
   for (const auto& vec : viewingVector) {
      for (const auto& symbol : vec) {
         std::cout << symbol << " ";
      }
      std::cout << std::endl;
   }
}


#include "ReelView.h"
#include <iostream>

ReelView::ReelView() {
   //This should probably never be called. You need a reel and reel stop info to know what to do
}

ReelView::ReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops) {
   populateReelView(reels, reelStops);
   populatePayLines();//This needs to be called after populateReelView. As it's dependent on ReelView state
   populatePayLineCombos();//This needs to be called after populatePayLines, it is dependent on PayLines states
}

void ReelView::populateReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops) {
   for (unsigned int row_index{ 0 }; row_index < reels.size(); ++row_index) {
      viewingVector.push_back(std::vector<symbol>{});//This creates a vector for each row
      for (unsigned int reel_index{ 0 }; reel_index < reels.size(); ++reel_index) {
         const auto& current_strip = reels[reel_index].getStrip();
         const auto& strip_stop = (reelStops[reel_index] + row_index) % current_strip.size(); //row_index increments the stop based on the row
         viewingVector[row_index].push_back(current_strip[strip_stop]);
      }
   }
}
void ReelView::populatePayLines()
{
   /*Here we need to create paylines - each will be different so we need to make them one at a time
      We still are trying to have a 'general' slot machine. So we need to make paylines relative to the
      size of reels.
   */
   const size_t reelCount = viewingVector.size();

   /*THESE NEED TO BE CHANGED OT NOT USE THE STATIC KEYWORD
      MAKE EACH PAYLINE LAMBDA JUST RETURN A VECTOR WITH THE CORRECT # and Value of indicies 0 < val < reel_count
   */
   payLines.push_back(PayLine{ [](int starting_index) {return starting_index; }, (reelCount /2) ,reelCount });// "Middle Payline"
   payLines.push_back(PayLine{ [](int starting_index) {static int increment = 0;  return starting_index + increment++; }, 0,reelCount }); //Upper left to Lower right
   payLines.push_back(PayLine{ [](int starting_index) {static int increment = 0;  return starting_index + increment--; }, reelCount -1, reelCount }); //LowerLeft to Upper RIght
   //printPayLineIndices(); //For debugging to see each payline index
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

void ReelView::activatePayLines(const int& desired_paylines)
{
   for (size_t payline_index{ 0 }; payline_index < desired_paylines; ++payline_index) {
      payLines[payline_index].setActive(true);
   }
}

void ReelView::deactivatePayLines()
{
   for (auto& payline : payLines) {
      payline.setActive(false);
   }
}

void ReelView::printPayLineCombos() const {
   int payline_count{ 1 };
   for (auto& paylinecombo : payLineCombos) {

      std::cout << "PAYLINE " << payline_count << " [" << (paylinecombo.isActive() ? "ACTIVE] :" : "INACTIVE] :");
      for (int index_ref{ 0 }; index_ref < paylinecombo.symbols.size(); ++index_ref) {
         std::cout << symbolToString(paylinecombo.symbols[index_ref]) << " ";
      }
      payline_count++;
      std::cout << std::endl;
   }
}

const std::vector<SymbolCombination> ReelView::getPayLineCombos() const {
   return payLineCombos;
}

int ReelView::validatePayLineNumInput(const char& cmd)
{
   //This function takes the cmd line input and checks to see (1) if it is numerical
   //(2) if it's a valid input for the desired number of paylines bet
   // If it is too few paylines or too many paylines it defaults to max paylines -> maxbet
   int num_paylines_bet{ 0 };
   if (isdigit(cmd)) {
      num_paylines_bet = static_cast<int>(cmd) - static_cast<int>('0');
   }
   if (num_paylines_bet < 1 || num_paylines_bet > payLineCount()) {
      num_paylines_bet = payLineCount();// If an invalid number of paylines is entered then just do max bet
   }
   return num_paylines_bet;
}

void ReelView::populatePayLineCombos() {
   for (size_t payLineIndex{ 0 }; payLineIndex < payLines.size(); payLineIndex++) {
      payLineCombos.push_back(SymbolCombination{}); //Make a payline combo for each payline
      const auto& currentPayLine = payLines[payLineIndex];
      auto& currentPayLineCombo = payLineCombos[payLineIndex];
      currentPayLineCombo.setActive(currentPayLine.isActive());
      for (size_t reel_index{ 0 }; reel_index < currentPayLine.size(); reel_index++) {
         //lopoing throough every reel and need to assign from correct index
         auto& payLineIndex = currentPayLine.getIndicies()[reel_index];
         currentPayLineCombo.symbols.push_back(viewingVector[payLineIndex][reel_index]); //Problem here
      }
   }
}

void ReelView::updatePayLineCombos() {
   for (size_t payLineIndex{ 0 }; payLineIndex < payLines.size(); payLineIndex++) {
      const auto& currentPayLine = payLines[payLineIndex];
      auto& currentPayLineCombo = payLineCombos[payLineIndex];
      currentPayLineCombo.setActive(currentPayLine.isActive());
      //Maybe consider making PayLineCombo constructor that takes a PayLine, then moving or emplacing the PayLine Combo into the container
      for (size_t reel_index{ 0 }; reel_index < currentPayLine.size(); reel_index++) {
         //lopoing throough every reel and need to check correct index
         auto& payLineIndex = currentPayLine.getIndicies()[reel_index];
         currentPayLineCombo.symbols[reel_index] = viewingVector[payLineIndex][reel_index];
      }
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
   updatePayLineCombos();
}

void ReelView::printReelView(const std::vector<Reel>& reels, const std::vector<unsigned int>& reelStops) const
{
   //Always prints a square viewing window rows=#ofreels
   //updateReelView(reels, reelStops); //Maybe have a flag to see if we need to do this. If nothing has changed (like no one has pulled the lever, then this in not necessary)
   //updatePayLineCombos(); //Needs to be called after updateReelView, allows for win/loss checking
   for (const auto& vec : viewingVector) {
      for (const auto& symbol : vec) {
         std::cout << symbolToString(symbol) << " ";
      }
      std::cout << std::endl;
   }
}


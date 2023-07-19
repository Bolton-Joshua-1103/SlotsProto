#include "CreditStateTracker.h"

CreditStateTracker::CreditStateTracker() 
   : CreditStateTracker(0 , "Default")
{
}

CreditStateTracker::CreditStateTracker(size_t starting_credits, std::string  _slot_id) 
   : credits(starting_credits), slot_id(_slot_id) {
   configureLoggingFile();  
}

CreditStateTracker::~CreditStateTracker() {
   outputfile.close();
}

bool CreditStateTracker::gamePlayed(const size_t& bet_price)
{
   if (true /*credits >= bet_price*/) {
      const int _bet_price_int = static_cast<int>(bet_price); //Change credits too size_t eventually
      credits -= _bet_price_int; //Debugging mode, endless play}
      credits_used += _bet_price_int;
      ++rounds_played;
      return true;
   }
   else return false;
}

void CreditStateTracker::gameWon(const size_t& _credits_won)
{
   const int _credits_won_int = static_cast<int>(_credits_won); //Change credits too size_t eventually
   credits += _credits_won_int;
   credits_won += _credits_won_int;
   ++rounds_won;
}

void CreditStateTracker::updateGameStats()
{
   //This is supposed to be called after a game cycle has been completed
   updatePayBackRate();
   updateHitRate();
   logCurrentState();
}

void CreditStateTracker::printgameStats()
{
   std::cout << "AVAILABLE CREDITS: " << getCredits() << std::endl;
   std::cout << std::endl;
   std::cout << "Credits Spent: " << getCreditsUsed() << std::endl;
   std::cout << "Credits Won: " << getCreditsWon() << std::endl;
   std::cout << "Rounds Played: " << getRoundsPlayed() << std::endl;
   std::cout << "Rounds Won: " << getRoundsWon() << std::endl;
   std::cout << std::endl;
   std::cout << "Current PayBackRate: " << getPayBackRate() << std::endl;
   std::cout << "Current HitRate: " << getHitRate() << std::endl;
   std::cout << std::endl;
}


void CreditStateTracker::updatePayBackRate()
{
   pay_back_rate = (float)credits_won / (float)credits_used;
}

void CreditStateTracker::updateHitRate()
{
   hit_rate = (float)rounds_won / (float)rounds_played;
}

void CreditStateTracker::configureLoggingFile()
{
   outputfile.open(slot_id + "data"); //Open file
   //Print variable headers
   outputfile << "SlotID" << "\t" << "RoundsPlayed" << "\t" << "RoundsWon" << "\t" << "CreditsUsed"
      << "\t" << "CreditsWon" << "\t" << "PayBackRate" << "\t" << "HitRate" << "\n";
}

void CreditStateTracker::logCurrentState()
{
   if (outputfile.is_open()) {
      outputfile << slot_id << "\t" << rounds_played << "\t" << rounds_won << "\t" << credits_used
         << "\t" << credits_won << "\t" << pay_back_rate << "\t" << hit_rate << "\n";
   }
   else std::cout << "OUTPUT FILE IS NOT OPEN" << std::endl;

}

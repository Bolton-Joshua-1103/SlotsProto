#include "CreditStateTracker.h"

CreditStateTracker::CreditStateTracker() : credits{ 0 }
{
}

CreditStateTracker::CreditStateTracker(const size_t& starting_credits) : credits(starting_credits) {
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
   updatePayBackRate();
   updateHitRate();
}

void CreditStateTracker::updatePayBackRate()
{
   pay_back_rate = (float)credits_won / (float)credits_used;
}

void CreditStateTracker::updateHitRate()
{
   hit_rate = (float)rounds_won / (float)rounds_played;
}
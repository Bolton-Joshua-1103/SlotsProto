#pragma once
class CreditStateTracker
{
public:
   
   //Constructors, always needs a starting amount of credits (which is determiend from the configuration)
   CreditStateTracker();
   CreditStateTracker(const size_t& starting_credits);

   bool gamePlayed(const size_t& bet_price);
   void gameWon(const size_t& credits_won);
   void updateGameStats();

   //Get Function for credits
   int getCredits() const { return credits; }

   //Get functions for recorded numbers
   size_t getCreditsUsed() const { return credits_used; }
   size_t getCreditsWon() const { return credits_won; }
   size_t getRoundsPlayed() const { return rounds_played; }
   size_t getRoundsWon() const { return rounds_won; }

   //Get functions for calculated numbers
   float getPayBackRate() const { return pay_back_rate; }
   float getHitRate() const { return hit_rate; }
private:

   //Tracked Numbers
   int credits; // THIS NEEDS TO BE A SIZE_T EVENTUALLY. THIS IS OUR COMPILER WARNING ABOUT SIZE_T TO INT CONVERSION. CHANGE WHEN NOT TESTING.

   //Recorded Numbers
   size_t credits_used{ 0 };
   size_t credits_won{ 0 };
   size_t rounds_played{ 0 };
   size_t rounds_won{ 0 };

   // Calculated Numbers
   float pay_back_rate{ 0 };
   float hit_rate{ 0 };

   void updatePayBackRate();
   void updateHitRate();
};


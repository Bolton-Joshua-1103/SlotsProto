#pragma once
#include <string>
#include <fstream>
#include <iostream>

class CreditStateTracker
{
public:
   
   //Constructors, always needs a starting amount of credits (which is determiend from the configuration)
   CreditStateTracker();
   CreditStateTracker(double, std::string, const std::string&);

   ~CreditStateTracker();

   bool gameRequested(const double& bet_price);
   void gameWon(const double& credits_won);
   void updateGameStats();
   void printgameStats();

   //Get Function for credits
   double getCredits() const { return credits; }

   //Get functions for recorded numbers
   double getCreditsUsed() const { return credits_used; }
   double getCreditsWon() const { return credits_won; }
   size_t getRoundsPlayed() const { return rounds_played; }
   size_t getRoundsWon() const { return rounds_won; }

   //Get functions for calculated numbers
   double getPayBackRate() const { return pay_back_rate; }
   double  getHitRate() const { return hit_rate; }

   //CreditStateTracker operator=(const CreditStateTracker& newCST);
private:

   //Slot identification and logging
   std::string slot_root;
   std::string slot_id;
   std::ofstream outputfile;

   //Tracked Numbers
   double credits; // THIS NEEDS TO BE A SIZE_T EVENTUALLY. THIS IS OUR COMPILER WARNING ABOUT SIZE_T TO INT CONVERSION. CHANGE WHEN NOT TESTING.

   //Recorded Numbers
   double credits_used{ 0 };
   double credits_won{ 0 };
   size_t rounds_played{ 0 };
   size_t rounds_won{ 0 };

   // Calculated Numbers
   double pay_back_rate{ 0 };
   double hit_rate{ 0 };

   void updatePayBackRate();
   void updateHitRate();

   void configureLoggingFile();
   void logCurrentState();
};


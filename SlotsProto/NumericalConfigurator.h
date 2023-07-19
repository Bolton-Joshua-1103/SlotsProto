#pragma once
#include <string>
class NumericalConfigurator
{

   /*
   COMBINATION EVALUATLOR SHOULD PROBABLY BE IN HERE
   BECAUSE YOU SHOULD BE ABLE TO CONFIGURE IT LIKE A PAY TABLE
   */

public:
   //Constructors
   NumericalConfigurator(); //Delegates defaults to parameterized ctor
   NumericalConfigurator(const int&, const int&);//Sets (starting_credits, cost_per_payline)

   // Get functions for configured numbers
   size_t get_cost_per_payline() const { return cost_per_payline; }
   size_t get_starting_credits() const { return starting_credits; }

   void set_cost_per_payline(const size_t& new_cost) { cost_per_payline = new_cost; }
private:

   //Configured numbers
   static constexpr int default_starting_credits = 0;
   static constexpr int default_cost_per_payline = 1;

   size_t cost_per_payline;
   size_t starting_credits;
};


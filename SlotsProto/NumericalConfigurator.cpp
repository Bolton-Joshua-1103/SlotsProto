#include "NumericalConfigurator.h"

NumericalConfigurator::NumericalConfigurator() : NumericalConfigurator(default_starting_credits, default_cost_per_payline) {

}

NumericalConfigurator::NumericalConfigurator(const int& _starting_credits, const int& _cost_per_payline) 
: starting_credits(_starting_credits), cost_per_payline(_cost_per_payline) {

}



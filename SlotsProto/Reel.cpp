#include "Reel.h"

Reel::Reel() : Reel::Reel(default_number_stops) {}

Reel::Reel(int num_stops) {
   if (num_stops > 10 || num_stops < 2) {
      num_stops = default_number_stops; //the num_stops requested is invalid
   }
   for (int symbolInt = 0; symbolInt < num_stops; symbolInt++) {
      strip.push_back(static_cast<symbol>(symbolInt));
   }
}
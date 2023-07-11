#include "Reel.h"

Reel::Reel() {
   for (size_t index{ 0 }; index < default_number_stops; ++index) {
      strip.push_back(static_cast<int>(index));
   }
}

Reel::Reel(int num_stops) {
   for (size_t index{ 0 }; index < num_stops; ++index) {
      strip.push_back(static_cast<int>(index));
   }
}
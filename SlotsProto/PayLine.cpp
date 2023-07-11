#include "PayLine.h"

PayLine::PayLine() {
   //Default
}

PayLine::PayLine(std::function<int(int)> index_func, size_t starting_index, const size_t& reel_view_length) {
   //Maybe needs to be an assert here or change return type to unsigned int.
   //The function returning a negative int will s
   for (int reel_index{ 0 }; reel_index < reel_view_length; reel_index++) {
      indicies.push_back(index_func(static_cast<int>(starting_index)));
   }
}

const std::vector<int>& PayLine::getIndicies() const
{
   return indicies;
}

size_t PayLine::size() const
{
   return indicies.size();
}

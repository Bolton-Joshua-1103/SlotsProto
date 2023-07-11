#pragma once
#include <string>


static unsigned int unique_symbol_count = 10;
enum class symbol : int {
   Apple = 0,
   Banana = 1,
   Cherry = 2,
   Grape = 3,
   Kiwi = 4,
   Lime = 5,
   Mango = 6,
   Orange = 7,
   Peach = 8,
   Pineapple = 9
};

std::string symbolToString(const symbol& symbol);
#include <iostream>
#include <conio.h>
#include <cctype>
#include "SlotMachine.h"

/*
THINGS TO DO:
   - IMPLEMENT BOOST FOR COMMAND LINE PARSING
   - COMBINE COMBINATION EVAULATOR AND NUMERICAL CONFIGURATOR, CE should be inside of NC
   - Add funcationality to provide paytable from external csv file
   - Implement RStudio program to use command line arguements to run a # of Slots and report on their aggregated data

*/


using namespace std;
bool done = false;

int main() {

   SlotMachine myslot{3, "Slot1"};
   myslot.printViewingWindow();

   char cmd{};
   while (!done) {
      if (_kbhit()) {
         system("cls");
         cmd = _getch();
         switch (cmd)
         {
         case('q'):
            done = true;
            break;
         default:
            myslot.playRound(cmd);
            break;
         }
      }
   }
}
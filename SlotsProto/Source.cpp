#include <iostream>
#include <conio.h>
#include "SlotMachine.h"


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
            myslot.playRound();
            break;
         }
      }
   }
}
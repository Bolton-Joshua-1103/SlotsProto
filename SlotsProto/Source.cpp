#include <iostream>
#include <conio.h>
#include "SlotMachine.h"


using namespace std;
bool done = false;

int main() {

   SlotMachine myslot{3};
   myslot.printViewingWindow();
   
   //for (int i = 0; i < 10000; ++i) {
   //   cout << "i: " << i << endl;
   //   myslot.playRound();
   //}
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
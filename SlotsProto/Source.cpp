#include <iostream>
#include <conio.h>
#include <cctype>
#include <type_traits>
#include "SlotMachine.h"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

/*
THINGS TO DO:
   - IMPLEMENT LOOPING BASED ON COMMAND LINE ARGUEMENTS, WHAT SHOULD THEY TYPE?
      -  CMDLINE(SlotsProt.exe -o Slot -i 1000 100,000) "slot" = slot1.csv, slot2.csv...slot1000.csv with 100,000 rounds played each
   - Need a flag to start/stop output. I think COUT is taking alot of my time in the loop...
   - COMBINE COMBINATION EVAULATOR AND NUMERICAL CONFIGURATOR, CE should be inside of NC [Not 100% necessary]
   - Add funcationality to provide paytable from external csv file
   - Implement RStudio program to use command line arguements to run a # of Slots and report on their aggregated data


DONE: 
   - IMPLEMENT BOOST FOR COMMAND LINE PARSING
*/


using namespace std;

boost::program_options::variables_map parseCommandLine(int argc, const char* argv[]) {
   using namespace boost::program_options;
   variables_map variables_map;

   try
   {
      options_description description{ "Options" };
      description.add_options()
         ("help,h", "Help info")
         ("output,o", value<std::string>(), "Output file.  Default: masterLog.txt")
         ("input,i", value<std::vector<int>>()->multitoken(), "Input Variables: # of Slots Desired, # of rounds Played Per Slot");

      // Allow a list of input files to be passed without a specific command line option
      positional_options_description pos_desc;
      pos_desc.add("input", -1);

      command_line_parser parser{ argc, argv }; //load parser with cmd line args
      parser.options(description).positional(pos_desc).allow_unregistered(); //formatting how to parce
      parsed_options parsed_options = parser.run();
      store(parsed_options, variables_map); // Loads variables_map with parsed cmd line arguments, this should be my input files?

      // Print the help to cout if help option specified
      if (variables_map.count("help"))
      {
         std::cout << "Utility program to combine multiple log files into a single log file." << std::endl;
         std::cout << "Assumes that individual log files are sorted (with numeric data as first field)." << std::endl;
         std::cout << description << std::endl;
      }
   }
   catch (const error& ex)
   {
      std::cout << ex.what() << std::endl;
   }


   return variables_map;

}


bool done = false;

int main(int argc, const char* argv[]) {

   auto&& variables_map = parseCommandLine(argc, argv);
   std::string output_var = variables_map["output"].as<std::string>();
   std::vector<int> input_vars = variables_map["input"].as<std::vector<int>>();
   //input_vars[0] = # of slot machines
   //input _vars[1] = # of runs for each slot machine
   const int slotNum = input_vars[0];
   const int slotRuns = input_vars[1];
   for (int index = 0; index < slotNum; ++index) {
      SlotMachine currentSlot{ 3, (output_var + to_string(index)), false};
      for (int round_index = 0; round_index < slotRuns; ++round_index) {
         currentSlot.playRound(3);
      }
   }


   //SlotMachine myslot{3, "Slot0", true};
   //myslot.printViewingWindow();

   //char cmd{};
   //while (!done) {
   //   if (_kbhit()) {
   //      system("cls");
   //      cmd = _getch();
   //      switch (cmd)
   //      {
   //      case('q'):
   //         done = true;
   //         break;
   //      default:
   //         myslot.playRound(cmd);
   //         break;
   //      }
   //   }
   //}
}
#include <iostream>
#include <conio.h>
#include <cctype>
#include <type_traits>
#include "SlotMachine.h"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

/*
THINGS TO DO:
   - Implement RStudio program to use command line arguements to run a # of Slots and report on their aggregated data
   - Add funcationality to provide paytable from external csv file
   - Implement slot options from command line --input #ofSlot, #ofRounds, #ofReels, PayLineConfig.csv
   - COMBINE COMBINATION EVAULATOR AND NUMERICAL CONFIGURATOR, CE should be inside of NC [Not 100% necessary]



DONE:
   - IMPLEMENT BOOST FOR COMMAND LINE PARSING
   - IMPLEMENT LOOPING BASED ON COMMAND LINE ARGUEMENTS
   - Need a flag to start/stop output.
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
         ("output,o", value<std::string>(), "Output file prefix, will always be ammended with #data  Default: default1data.txt")
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
         std::cout << "Slot Machine Simulator, can either be played in the console or run for desired rounds via command line" << std::endl;
         std::cout << "Takes command line arguements and outputs round by round stats to desiredfile." << std::endl;
         std::cout << "If no inputs from command line are given then console play is defaulted to. Example: [SlotsProto.exe --output slot1] will default to console play and store data in slot1data.txt" << std::endl;
         std::cout << "CommandLine: SlotsProto.exe --output{FolderRoot\FilePrefix} --input{#MachinesToTest} {#RoundsToPlay}" << std::endl;
         std::cout << "This command will create the same number of files as slot machine requested with format of \"{PREFIX OF FILE} + {#}data.txt\" as the file name.All the way up till the desired number of files." << std::endl;
         std::cout << "Example : [SlotsProto.exe --output newSlotDesign --input 100 10000]" << std::endl;
         std::cout << "This command will create 100 new slot machines(and thus files) all titled(newSlotDesign1data.txt, newSlotDesign2data.txt, ...., newSlotDesign100Data.txt) where each file contains 10,000 lines of data." << std::endl;
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

   std::string output_var = "defaultSlot";
   auto&& variables_map = parseCommandLine(argc, argv);

   if (variables_map.count("output")) {
      output_var = variables_map["output"].as<std::string>();
   }

   if (variables_map.count("input")) {
      std::vector<int> input_vars = variables_map["input"].as<std::vector<int>>();
      const int slotNum = input_vars[0];    //input_vars[0] = # of slot machines
      const int slotRuns = input_vars[1];    //input _vars[1] = # of runs for each slot machine
      for (int index = 1; index <= slotNum; ++index) {
         SlotMachine currentSlot{ 3, (output_var + to_string(index)), false };
         for (int round_index = 0; round_index < slotRuns; ++round_index) {
            currentSlot.playRound(3);
         }
      }
   }
   else {
      SlotMachine myslot{ 3, output_var, true };
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
}
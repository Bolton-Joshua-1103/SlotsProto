#include <iostream>
#include <conio.h>
#include <cctype>
#include <type_traits>
#include <functional>
#include <thread>
#include <future>
#include <chrono>
#include "SlotMachine.h"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

/*
THINGS TO DO:
   - Create functionality to create logging files for longer term performance (small number of slots) or short term performance with many slots
   - Implement logging that logs combinations won and compare to frequency designed on the paytable. They should match after large n runs.
   - Add funcationality to provide paytable from external csv file
   - Implement slot options from command line --input #ofSlot, #ofRounds, #ofReels, PayLineConfig.csv
   - COMBINE COMBINATION EVAULATOR AND NUMERICAL CONFIGURATOR, CE should be inside of NC [Not 100% necessary]



DONE:
   - Implement RStudio program to use command line arguements to run a # of Slots and report on their aggregated data
   - IMPLEMENT BOOST FOR COMMAND LINE PARSING
   - IMPLEMENT LOOPING BASED ON COMMAND LINE ARGUEMENTS
   - Need a flag to start/stop output.
*/

#define dbg(x) std::cout << #x << ": " << (x) << std::endl;

using namespace std;

boost::program_options::variables_map parseCommandLine(int argc, const char* argv[]) {
   using namespace boost::program_options;
   variables_map variables_map;

   try
   {
      options_description description{ "Options" };
      description.add_options()
         ("help,h", "Help info")
         ("output,o", value<std::string>(), "Output file root + prefix, example --output C:\\Users\\Jbolt\\source\\repos\\SlotsProto\\SlotsProto\\GeneratedSlotsData\\SlotData \nThis will generate files SlotData1, SlotData2,... in the folder GeneratedSlotsData")
         ("input,i", value<std::vector<int>>()->multitoken(), "Input Variables: # of Slots Desired, # of rounds Played Per Slot, # of default reels on slot machine");

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
         std::cout << "If no inputs from command line are given then console play is defaulted to. Example: [SlotsProto.exe --output slot1] will default to console play and store data in slot1data.txt, in the local project folder" << std::endl;
         std::cout << "CommandLine: SlotsProto.exe --output{FolderRoot/DataPrefix} --input {#MachinesToTest} {#RoundsToPlay} {Default Reels Desired}" << std::endl;
         std::cout << "This command will create the same number of files as slot machine requested with format of \"{PREFIX OF FILE} + {#}\" as the file name.All the way up till the desired number of files." << std::endl;
         std::cout << "Example : [SlotsProto.exe --output C:\\Users\\Jbolt\\source\\repos\\SlotsProto\\SlotsProto\\GeneratedSlotsData\\NewSlotDesign --input 100 10000 3]" << std::endl;
         std::cout << "This command will create 100 new slot machines(and thus files) each with 3 reels, all titled(newSlotDesign1, newSlotDesign2, ...., newSlotDesign100) where each file contains 10,000 lines of data." << std::endl;
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

   std::string output_path = "defaultSlot";
   auto&& variables_map = parseCommandLine(argc, argv);

   if (variables_map.count("output")) {
      output_path = variables_map["output"].as<std::string>();
   }

   if (variables_map.count("help")) {
      cout << "\nHelp Requested: exitting" << endl;
   }

   else if (variables_map.count("input")) {
      //Just uses the first 3 command line arguements
      std::vector<int> input_vars = variables_map["input"].as<std::vector<int>>();
      const int slotNum = input_vars[0];    //input_vars[0] = # of slot machines
      const int slotRuns = input_vars[1];    //input _vars[1] = # of runs for each slot machine
      const int slotReels = input_vars[2]; //input_vars[2] = # of reels desired
      const auto start = std::chrono::steady_clock::now();

      //Creating each slots play, caputuring the number of runs, number of reels, and output
      function<void(int)> slotMachineRun = [slotRuns, slotReels, output_path](int index) {
         SlotMachine currentSlot{ slotReels, "SlotData" + to_string(index), (output_path + to_string(index)), false };
         for (int round_index = 0; round_index < slotRuns; ++round_index) {
            currentSlot.playRound(3);
         }
      };

      std::vector<future<void>> futures;
      for (int index{ 0 }; index < slotNum; ++index) {
         //function<void()> temp = [index = index, slot = slotMachineRun]() {slot(index); };
         futures.emplace_back(std::async(std::launch::async, slotMachineRun, index));//Starting threads as we build them, futures.wait() will determine when thread is rejoined.
      }
      dbg(futures.size());
      for (const auto& future : futures) {
         future.wait();
      }

      const auto end = std::chrono::steady_clock::now();
      const std::chrono::duration<double> elapsed_seconds = end - start;
      cout << "DURATION: " << elapsed_seconds.count() << endl;

   }
   else {
      SlotMachine myslot{ 3, "Slotdata", output_path, true };
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
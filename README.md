# SlotsProto

Simulates a simple slot machine.

Takes command line arguements and outputs round by round stats to desiredfile

CommandLine: SlotsProto.exe --output {PREFIX OF FILE} --input {NUMBER OF SLOT MACHINES TO TEST} {HOW MANY ROUNDS TO PLAY ON EACH SLOT MACHINE}
This command will create the same number of files as slot machine requested with format of "{PREFIX OF FILE} + {#}data.txt" as the file name. All the way up till the desired number of files.
Example: [SlotsProto.exe --output newSlotDesign --input 100 10000]
This command will create 100 new slow machines (and thus files) all titled (newSlotDesign1data.txt, newSlotDesign2data.txt,....,newSlotDesign100Data.txt) where each file contains 10,000 lines of data.
This data then can be interpreted through a seperate program or it can be agregatted and anlayzed in data visualization tools like RStudio. This is my approach and future additions to the program will
add a report for each slot machine and add a report for all the aggegrated data created by the slot machines.

Each file will have rows of data seperated by tab delimeteres. The rows represent indiviudal rounds and reflect state variables as well as calculated hit rate and PBR:
The columns of the data set are: 
[SlotID{string}]  [RoundsPlayed{int}] [RoundsWon{int}] [CreditsUsed{int}] [CreditsWon{int}] [PayBackRate{int}] [HitRate{int}]


The program supports:
Different reel sizes, reel configurations and reel counts.
Variable paylines that use lambdas to denote payline orientations
Boost command line parsing to determine ouput such as, # of slot machines to run, how many rounds to run, whether to print output to command line, and fileformat of outputfile. 
Prints to output logs and calculates state varaibles like credits spent, credits earned, rounds won, rounds played, hitrate, paybackrate
Currently has built in support for a paytable for any number of reels. This 'default' paytable has a 1.0 PBR and hit rate dependent on the number of reels selected. The Hit rate is 3% when there are 3 reels.

Future features intended for addition include:
Paytable configuration from properly formatted excel file (Any slot machine should be able to run any paytable)
Concurrent threads for logging and printing to increase efficiency
Scatter paylines
Playtime Report Summary for individual slots and summary data for aggregrated slot runs.


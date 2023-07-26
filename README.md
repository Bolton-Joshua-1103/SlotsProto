# SlotsProto

Simulates a simple slot machine.

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


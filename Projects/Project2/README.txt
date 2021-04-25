Nathaniel Fenoglio 1001634050
Lemuel Rivera 1000842851

**************************************************
Files included:
Project2Report.docx

Assignment_1.c
Assignment_2.c
strings.txt
message.txt

measureSingle2.c
measureSwitch2.c
util.c
util.h
cpuinfo.txt

Project2Report.docx

**************************************************
Assignment_1.c finds the number of matches of a substring in a larger string using multithreading and allowing for user to specify the number of threads to do work on the string.
The strings to be checked are to be included in a file string.txt on 2 separate lines with the string to search through on line 1 and the string to search for on line 2.

Assignment_2.c is a solution to the producers and consumers problem using multithreading. The producer thread puts characters, one at a time, in a buffer that is read from by the consumer thread who prints the message to the screen.
The message is to be read from a file named message.txt.

Assignment_3 is an unsuccessful attempt at writing a benchmark test program to measure the context switching costs associated with multiple threads.

**************************************************
Compilation instructions:


Assignment 1:
include a text file named strings.txt of the format: 
	string_that_you_will_search_on_1st_line
	string_to_match_on_2nd_line

then compile and run with below commands:
gcc -o count_str_matches Assignment_1.c -lpthread
./count_str_matches

The amount of threads is able to be varied by changing the #define NUM_THREADS #to whatever # of threads that you desire.


Assignment 2:
include a text file named message.txt with text to be "produced and consumed" by the program

then compile and run with below commands:
gcc -o producers_consumers Assignment_2.c -lpthread
./producers_consumers 


Assignment 3:
gcc -o measureSingle measureSingle2.c util.c util.h -lpthread
./measureSingle

gcc -o measureSwitch measureSwitch2.c util.c util.h -lpthread
./measureSwitch



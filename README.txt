Files involved;
.spellconf ----------- this is where the settings are configured

check.h -------------- the header file for check.o that was provided

check.o -------------- this is what checks the spelling of the input file, this
                       file was provided

fileIO.c ------------- handles all the input and output from files

fileIO.h ------------- the header file for fileIO.c that with declaration for
                       other .c files to use

LinkedList.c --------- this is where the all list operations are handled

LinkedList.h --------- the header file for LinkedList.c that has all it's forward
                       declaration for other files to use

makefile ------------- this is how the program is compiled and tested

main.c --------------- this is what starts the operation of the program

spellChecker.c ------- this is the file that calls and edits the input file

spellChecker.h ------- the header file for spellChecker.c that forward declares
                       all the method and stores certain structs and constants

stringArraystuff.c --- this handles all the string array operations

stringArraystuff.h --- the header file for stringArrayStuff.c that forward declares
                       all it's functions


Compiling:
to compile the program from terminal simply type "make" where the directory is
located.


.spellconf:
Before you run the program you must enter your preferences into the .spellconf
file the format is as follows:

maxdifference = [positive integer value]
autocorrect = [yes/no]
dictfile = [dictionary file name]

the order of these is not important, but each word must be separated by a space
and you'll need to input all 3 to run the program.


Test:
to run a simply test of the program with the sample input file provided type
"make test" into the terminal. To run the test with valgind simply type
"make val" into the terminal.

testing of the program was done in room 314.232 on computer 6N56HZ1


Run:
to run the application type "./spellCheck [file name]" into the terminal, the [file name]
is the name of the file to be spell checked.


Bugs:
- if the .spellconf isn't spaced out appropriately the settings cannot be read
- the spell checker gets rid of punctuation
- the program can be very slow if it's been run through valgrind
- correctly spelt words are occasionally changed
- if there is a certain number of newlines between the settings text, there is
  a change some of the setting won't be read

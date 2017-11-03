/****************************************************************************
 * FILE: main.c
 * AUTHOR: Emmanuel Iloh
 * Student Number: 18817599
 * UNIT: UNIX and C Programming (COMP1000)
 * PURPOSE: initilises the program
 * REFERENCE: none
 * LAST MOD: 2017-10-27
 * COMMENTS:
 *****************************************************************************/

#include "spellChecker.h"

/****************************************************************************
 * NAME: main
 * PURPOSE: handles the functionality of the program and calls the relevant
 *          functions
 * IMPORTS: argc and argv, the number of arguments from the terminal and an
 *          array of strings of all those arguments
 * EXPORTS: an int for the exit status of the program
 * ASSERTIONS:
 *****************************************************************************/
int main(int argc, char *argv[])
{
   if(argc < 2)
   {
      printf("not enough arguments, please add the file name\n");
   }
   else if (argc > 2)
   {
      printf("you have too many arguments\n");
   }
   else
   {
      spellChecker(argv[1]);
   }
   return 0;
}

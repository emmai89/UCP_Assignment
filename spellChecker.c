/****************************************************************************
 * FILE: spellChecker.c
 * AUTHOR: Emmanuel Iloh
 * Student Number: 18817599
 * UNIT: UNIX and C Programming (COMP1000)
 * PURPOSE: checks if the contents of a words in a text file are spelt correctly
 *          and depending on the settings corrects the spelling
 * REFERENCE: none
 * LAST MOD: 2017-10-27
 *****************************************************************************/

#include "spellChecker.h"

/****************************************************************************
 * NAME: spellChecker
 * PURPOSE: handles most of the functionality of the program
 * IMPORTS: char *fileName, the user file name
 * EXPORTS: nothing
 * ASSERTIONS:
 *****************************************************************************/
void spellChecker(char* fileName)
{
   ActionFunc action;
   Settings *settings;
   LinkedList *dictionary, *fileWords;
   char **dictWords, **text, setFile[MAX_FILE_NAME];
   int numDictionary, numWords;

   strcpy(setFile, ".spellconf");
   printf("**************** opened the settings file **************\n");
   settings = readSettings(setFile);    /*this passes the file name to the readSettings function*/
   if(settings == NULL)
   {
      printf("\nThe settings file was invalid, make sure the spacing is correct\n");
   }
   else
   {
      printf("\n************ These are your setting ***************\n");
      printSetting(settings);
      printf("*****************************************************\n");

      printf("\n************ Reading Dictionary File **************\n");
      dictionary = readWords(settings->dictFile);

      printf("\n************ Reading User File **************\n");
      fileWords = readWords(fileName);

      if(dictionary != NULL && fileWords != NULL)
      {
         printf("*********** Both file successfully read ***********\n");
         numDictionary = dictionary->length;
         dictWords = listToArray(dictionary, numDictionary);

         numWords = fileWords->length;
         text = listToArray(fileWords, numWords);

         if(settings->autoCorrect)
         {
            action = &autoCallBack;
         }
         else
         {
            action = &callBack;
         }

         check(text, numWords, dictWords, numDictionary, settings->maxDiff, action);
         writeWords(fileName, text, numWords);

         freeArrayOfStrings(text, numWords);
         freeArrayOfStrings(dictWords, numDictionary);
      }
      if(dictionary != NULL)
      {
         freeLinkedList(dictionary);
      }
      if(fileWords != NULL)
      {
         freeLinkedList(fileWords);
      }
      fullFree(settings);
   }
}

/****************************************************************************
 * NAME: printSetting
 * PURPOSE: prints the contents of the settings
 * IMPORTS: Settings *, the current settings
 * EXPORTS: nothing
 * ASSERTIONS:
 *****************************************************************************/
void printSetting(Settings* settings)
{
   printf("%s\n%d\n%d\n", settings->dictFile, settings->maxDiff,
          settings->autoCorrect);
}

/****************************************************************************
 * NAME: callBack
 * PURPOSE: frees an array of stings at a given size TODO:\ finsh this
 * IMPORTS: num, the size of the array of strings
 * EXPORTS: nothing
 * ASSERTIONS:
 *****************************************************************************/
int autoCallBack(char* word, char* suggestion)
{
   int change = FALSE;

   if(suggestion != NULL)
   {
      change = TRUE;
   }

   return change;
}

/****************************************************************************
 * NAME: callBack
 * PURPOSE: frees an array of stings at a given size TODO: finsh this
 * IMPORTS: num, the size of the array of strings
 * EXPORTS: nothing
 * ASSERTIONS:
 *****************************************************************************/
int callBack(char* word, char* suggestion)
{
   int change = autoCallBack(word, suggestion);
   char choice;

   if(change)
   {
      printf("\nDo you want to swap '%s' with '%s'\n", word, suggestion);

      choice = yesOrNo();

      if(choice == 'N')
      {
         change = FALSE;
      }
   }

   return change;
}

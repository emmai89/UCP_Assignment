/****************************************************************************
 * FILE: fileIO.c
 * AUTHOR: Emmanuel Iloh
 * Student Number: 18817599
 * UNIT: UNIX and C Programming (COMP1000)
 * PURPOSE: read of the setting file and the contents of text files
 * REFERENCE: the content of this file was based on the lecture notes previous
 *  practicals
 * LAST MOD: 2017-10-14
 * COMMENTS: possible errors with segmental faults if inputs are too long
 *****************************************************************************/

#include "fileIO.h"

/****************************************************************************
 * NAME: readSettings
 * PURPOSE: read the contents of the .spellconf file and storing it
 * IMPORTS: fileName, a string of the filename
 * EXPORTS: settings, the setting read from the in a Settings struct
 *****************************************************************************/
Settings* readSettings(char* fileName)
{
   FILE *fp = fopen(fileName, "r");
   Settings *settings = (Settings*)malloc(sizeof(Settings));
   char choice[MAX_WORD_LENGTH], option;
   int count[] = {FALSE, FALSE, FALSE};

   if(fp == NULL)
   {
      perror("cannot open the file");
      nullFree(&settings);
   }
   else
   {
      printf("\n*************** successfully opened **********************\n");

      while(readWord(fp, choice) != EOF)
      {
         option = 'Y';
         if(choice == NULL)
         {
            perror("invalid format of file");
            nullFree(&settings);
         }
         else
         {
            if(strcmp(choice, "dictfile") == 0) /*these are the conditions of the*/
            {                                   /*dictfile option*/
               if(count[0])
               {
                  printf("\ndo you want to override the dictionary file %s\n",
                         settings->dictFile); /*this is to check if this settting has*/
                  option = yesOrNo();          /*already been chosen*/
               }

               if(option == 'Y' || option == 'y') /*the old settings will be ovveriting*/
               {
                  if(fscanf(fp, "= %256s ", settings->dictFile) != 1)/*256 is the max file*/
                  {                                                 /*allowed in linux*/
                     perror("invalid format of file");
                  }
                  else
                  {
                     /*flushLine(fp);*/
                     count[0] = TRUE; /*this is when something has successfully been*/
                  }                   /*entered into the the dictfile setting*/
               }
               else
               {
                  fgets(choice, MAX_WORD_LENGTH, fp); /*if it's not to be ovveriten*/
               }                                     /*the rest of the line is cleared*/
            }
            else if(strcmp(choice, "maxdifference") == 0)
            {
               if(count[1])
               {
                  printf("\ndo you want to override the max difference %d\n",
                         settings->maxDiff);
                  option = yesOrNo(); /*same concept as above*/
               }

               if(option == 'Y' || option == 'y')
               {
                  if(fscanf(fp, " = %d ", &settings->maxDiff) != 1)
                  {
                     perror("invalid value for max difference");
                     flushLine(fp);
                     /*not valid*/
                  }
                  else
                  {
                     if(settings->maxDiff >= 0 && settings->maxDiff <= 9)
                     {
                        count[1] = TRUE;
                     }
                  }
               }
               else
               {
                  fgets(choice, MAX_WORD_LENGTH, fp); /*see above*/
               }
            }
            else if(strcmp(choice, "autocorrect") == 0)
            {
               if(count[2]) /* if there is already something saved in autocorrect*/
               {
                  printf("\ndo you want to override the autoCorrect value of %d\n",
                         settings->autoCorrect);
                  option = yesOrNo();
               }

               if(option == 'Y' || option == 'y')
               {
                  if(fscanf(fp, "= %3s ", choice) != 1)
                  {
                     perror("invalid format of file");
                  }
                  else
                  {

                     if(strcmp(choice, "yes") == 0)
                     {
                        settings->autoCorrect = 1;
                        count[2] = TRUE;
                     }
                     else if(strcmp(choice, "no") == 0)
                     {
                        settings->autoCorrect = 0;
                        count[2] = TRUE;
                     }
                     else
                     {
                        printf("%s", choice); /*if yes or no were not chosen, this message is shown*/
                        flushLine(fp);
                        perror(" is not valid, autoCorrect must contain yes or no!!");
                     }
                  }
               }
               else
               {
                  fgets(choice, MAX_WORD_LENGTH, fp); /* if the user does not choose to override*/
               }                       /*the rest of the line is just ignored*/
            }
            else
            {
               printf("\n%s", choice);
               perror(" is not one of the settings");
               fgets(choice, MAX_WORD_LENGTH, fp);
            }
         }
      }
   }
   fclose(fp);

   if(!count[0]) /*the next 3 if statements check if the things read from the */
   {               /*settings file were enough, if not, it tell the user which and returns NULL*/
      printf("\nNo dictionary file name found\n");
      nullFree(&settings);
   }
   if(!count[1])
   {
      printf("\nNo max difference found\n");
      if(settings != NULL)
      {
         nullFree(&settings);
      }
   }
   if(!count[2])
   {
      printf("\nNo autoCorrect found\n");
      if(settings != NULL)
      {
         nullFree(&settings);
      }
   }

   return settings;
}

/****************************************************************************
 * NAME: readWords
 * PURPOSE: Read all the words from text file and store them
 * IMPORTS: fileName, a string of the name of the file to be read
 * EXPORTS: a LinkedList with all the contengts of the file
 * ASSERTIONS:
 *****************************************************************************/
LinkedList* readWords(char* fileName)
{
   FILE *fp = fopen(fileName, "r");
   LinkedList* words;
   char temp[MAX_WORD_LENGTH], *word;

   if(fp == NULL)
   {
      perror("cannot open the file");
      words = NULL;
   }
   else
   {
      printf("\n************* successfully opened ***************\n");
      words = emptyList(); /*it's initilized as an empty list with no data */
      while (readWord(fp, temp) != EOF)
      {
         if(temp == NULL)
         {
            perror("there was nothing there");
         }
         else
         {
            word = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
            strncpy(word, temp, MAX_WORD_LENGTH); /*it copied the word in teh file to a difference*/
            insertLast(words, word);  /*memory address to a void ovveriting the word*/
         }
      }
      if(temp[0] == CLEAR)
      {
         freeLinkedList(words);
         words = NULL;
      }
      fclose(fp);
   }

   return words;
}

/****************************************************************************
 * NAME: readWord
 * PURPOSE: to read a word from the file under 50 characters
 * IMPORTS: FILE *fp and char[] to be written to
 * EXPORTS: int of 0, but eof, if it is reached
 *****************************************************************************/
int readWord(FILE *fp, char word[])
{
   char ch, *text;
   int length = 0, end = 0;
   text = (char*)calloc(MAX_WORD_LENGTH, sizeof(char));

   do
   {
      if(length < MAX_WORD_LENGTH) /*ensures no words are above the max*/
      {
         ch = fgetc(fp);
         if((ch == ' ' || ch == '\n') && length == 0)
         {
            ch = 'p';
         }
         else if(ch == ' ' || ch == '\n' || ch == '\0') /*difference cases depending*/
         {                                              /*on the current char value*/
            text[length] = '\0'; /*for the end of the file*/
         }
         else if(ch == EOF)
         {
            end = EOF;/*return eof if it is the end*/
         }
         else
         {
            text[length++] = ch; /*each character been pasted in, and index increased*/
         }
      }
      else
      {
         printf("\nThis is an invalid file with a word(s) over 50 characters\n");
         free(text);
         text = NULL;
         end = EOF; /*instantly closes the file*/
         ch = EOF;
         word[0] = CLEAR; /*a flag to stop reading and clear the loinked list*/
      }
   } while(ch != ' ' && ch != '\0' && ch != '\n' && ch != EOF);

   if(text != NULL)
   {
      strncpy(word, text, MAX_WORD_LENGTH); /*copies the read word to be exported*/
      fullFree(text);
   }

   return end;
}

/****************************************************************************
 * NAME: writeWords
 * PURPOSE: Read all the words from text file and store them
 * IMPORTS: fileName, a string of the name of the file to be read
 * EXPORTS: a LinkedList with all the contengts of the file
 * ASSERTIONS:
 *****************************************************************************/
void writeWords(char* fileName, char* text[], int size)
{
   FILE *fp = fopen(fileName, "w");
   int ii, length = 0;

   if(fp == NULL)
   {
      perror("cannot open the file");
   }
   else
   {
      for(ii = 0; ii < size; ii++)
      {
         length += strnlen(text[ii], MAX_WORD_LENGTH); /*this keeps the length of each line */
         if(length >= 60)                    /*under 60 characters long*/
         {
            fputc('\n', fp);
            length = 0;
         }
         if(fprintf(fp, "%s ", text[ii]) == 1)
         {
            perror("error while writing to file");
         }
      }
      fclose(fp);
   }
}

/****************************************************************************
 * NAME: nullFree
 * PURPOSE: free's the settings pointer and sets it to NULL
 * IMPORTS: ptr, a pointer to a Settings pointer
 * EXPORTS: nothing
 * ASSERTIONS:
 *****************************************************************************/
void nullFree(Settings** ptr)
{
   free(*ptr);
   *ptr = NULL;
}

/****************************************************************************
 * NAME: yesOrNo
 * PURPOSE: get the user to either input a Y or N
 * IMPORTS: nothing
 * EXPORTS: either the char 'Y' or 'N'
 * ASSERTIONS:
 *****************************************************************************/
char yesOrNo()
{
   char option[2];

   do
   {
      printf("\nplease enter Y or N\n");
      scanf("%2s", option); /*only takes the first 2 chars*/
      flush(); /*clears out any extra inputs*/
      if(strnlen(option, 2) != 1) /*ensures there is no more that on char in the terminal*/
      {
         printf("Only enter a single char\n"); /*error message*/
         option[0] = 'h';
      }
   } while(option[0] != 'N' && option[0] != 'Y' && option[0] != 'n' &&
           option[0] != 'y');         /* it loops until the user enters Y or N*/

   return option[0]; /*returns y, n etc*/
}

/****************************************************************************
 * NAME: flush
 * PURPOSE: clears the terminal input before the next input
 * IMPORTS: nothing
 * EXPORTS: nothing
 * COMMENTS: adapted from: https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
 *           by: jamesdlin
 *****************************************************************************/
void flush()
{
   while (getchar() != '\n') /*loops until all the contents of the terminal are gone*/
   {

   }
}

/****************************************************************************
 * NAME: flushLine
 * PURPOSE: clears the rest of teh line in the file
 * IMPORTS: FILE *f of the current file
 * EXPORTS: nothing
 * COMMENTS: adapted from: https://stackoverflow.com/questions/6138172/flushing-buffer-with-fgets
 *           by: pmg
 *****************************************************************************/
void flushLine(FILE *f)
{
   char c;

   do
   {
      c = fgetc(f); /*gets all the values on the line until the new line char */
   }
   while (c != '\n' && c != EOF);
}

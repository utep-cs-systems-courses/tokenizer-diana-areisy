#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

int space_char(char c)
{
  return(c == ' ' || c == '\t')&& c != '\0';
}

int non_space_char(char c)
{
  return c != ' ' && c != '\t' && c!= '\0';
}

char *word_start(char *str)
{
  for(int i = 0; space_char(*str); str++)
    {
    }
  return str;
}

char *word_terminator(char *word)
{
 
  int i = 0;
  while(*(word+i)){
    if(space_char(*(word + i))){
      return word + i;
    }
    i++;
  }
  return word + i;
}

int count_words(char *str)
{
  int inWord = 0;
  int wordCount = 0;

  while(*str != '\0')
    {
      if(non_space_char(*str) && inWord == 0)
	{
	  wordCount++;
	  inWord = 1;
	}
      else if(space_char(*str) == 1 && inWord == 1)
	{
	  inWord = 0;
	}
      str++;
    }
  return wordCount;
}

char *copy_str(char *inStr, short len)
{
  char *out_str =(char*) malloc(sizeof(char) * len + 1);

  char*c = out_str;

  for(short i = 0; i < len; i++)
    {
      *c = *inStr;

      if(*c == '\0')
	{
	  break;
	}
      c++;
      inStr++;
    }
  *c = '\0';

  return out_str;
}

char **tokenize(char* str)
{
  int words = count_words(str);
  char **tokens = malloc(sizeof(char*) * (words + 1));

  str = word_start(str);
  for(int i = 0; i  < words; i++)
    {
      char* terminator = word_terminator(str);
      tokens[i] = copy_str(str, terminator-str);

      str = word_start(terminator);
    }
  char **terminator = tokens + words;
  *terminator = 0;


  return tokens;
}

void print_tokens(char ** tokens)
{
  printf("{\n");
  for(char** token = tokens; *token != 0; token++)
    printf("\t[%ld] '%s' \n", token - tokens, *token);
  printf("}\n\n");
}

void free_tokens(char **tokens)

{
  int i = 0;
  while(tokens[i])
    {
      free(tokens[i]);
      i++;
    }
  free(tokens);
}

#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"

#define BUFFER_SIZE 100

static void process_input(char *user_input, List *history, int history_length)
{
  if(user_input[1] == ' ' || user_input[1] == '\0' || user_input[1] == 'h')
    {
      printf("\t~~~~History~~~~\n");
      print_history(history);
      printf("\t-----------------\n");
    }
  else if(user_input[1] == 'q')
    {
      free_history(history);
      puts("~~~~Existing~~~~\n");
      exit(EXIT_SUCCESS);
    }
  else
    {
      int asked_index = atoi(user_input + 1);
      
      if(asked_index > 0)
	{
	  char *str = get_history(history, asked_index);
	  
	  if(!str)
	    {
	      puts("~~~~No history found at given index~~~~");
	      return;
	    }
	  char **tokens = tokenize(str);
	  print_tokens(tokens);
	  free_tokens(tokens);
	}
      else
	{
	  puts("~~~~~Invalid Index~~~~~");
	  return;
	}
    }
}
int main()
{
  
  char user_input[BUFFER_SIZE];
  List *history = init_history();
  char **tokens;
  int history_length = 0;

  puts("Welcome to Tokenizer");
  puts("What would you like to do: \n 1. Input a String.\n\t2.'!<num>' To print a past entry.\n\t3. '!h'|'!' Display all previous entries. \n\t4. '!q' Quit ");

  while(1)
    {
      printf("> ");
      fgets(user_input, BUFFER_SIZE, stdin);

      if(user_input[0] == '!')
	{
	  process_input(user_input, history, history_length);
	}
      else
	{
	  puts(user_input);
	  add_history(history, user_input);
	  history_length++;
	}
    }
}

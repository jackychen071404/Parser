#include "myshell_parser.h"
#include "stddef.h"
#include <stdlib.h>
#include <string.h>

struct pipeline *pipeline_build(const char *command_line) {
  struct pipeline *pipe = malloc(sizeof(struct pipeline));
  pipe->is_background = 0;
  pipe->commands = NULL;

  struct pipeline_command *first = malloc(sizeof(struct pipeline_command));
  for(int i = 0; i < MAX_ARGV_LENGTH; i++)
    {
      first->command_args[i] = NULL;
    }
  first->next = NULL;
  first->redirect_in_path = NULL;
  first->redirect_out_path = NULL;

  struct pipeline_command *current = NULL;

  pipe->commands = first;
  current = first;

  int index = 1;
  int i = 0;

  while(command_line[i]!='\0') //empty
    {
      if(command_line[i] == ' ' || command_line[i] == '\n' || command_line[i] == '\t')
	i++;
      else if(command_line[i] == '>')
	{
	  i++;
	  if(current->redirect_out_path != NULL)
	{
	  pipeline_free(pipe);
	  return NULL;
	}
	  char *out = malloc(MAX_LINE_LENGTH); //memory for redirect_out 
	  while(command_line[i]==' ' || command_line[i] == '\n' || command_line[i] == '\t')
	    i++;
	  if(command_line[i] == '&' || command_line[i] == '>' || command_line[i] == '<' || command_line[i] == '|')
	{
	  pipeline_free(pipe);
	  return NULL;
	}
	  int j = 0;
	  while(command_line[i] != ' ' && command_line[i] != '\t' && command_line[i] != '\n' && command_line[i] != '&' &&command_line[i] && '>' != command_line[i] && '<' && command_line[i] != '|')
	{
	  out[j] = command_line[i];
	  i++;
	  j++;
	}
      current->redirect_out_path = out;
	}
      else if(command_line[i] == '&') //parser in background
	{
	  i++;
	  pipe->is_background = 1;
        }
    else if(command_line[i] == '<')
      {
	i++;
	if(current->redirect_in_path != NULL)
	  {
	    pipeline_free(pipe);
	    return NULL;
	  }
	char *in = malloc(MAX_LINE_LENGTH); //memory for redirect_in
	while(command_line[i]==' ' || command_line[i] == '\n' || command_line[i] == '\t')
	  i++;
	if(command_line[i] == '&' || command_line[i] == '>' || command_line[i] == '<' || command_line[i] == '|')
	  {
	    pipeline_free(pipe);
	    return NULL;
	  }
	int j = 0;
	while(command_line[i] != ' ' && command_line[i] != '\t' && command_line[i] != '\n' && command_line[i] != '&' && command_line[i] != '>' && command_line[i] != '<' && command_line[i] != '|')
	  {
	    in[j] = command_line[i];
	    i++;
	    j++;
	  }
	current->redirect_in_path = in;
      }
    else if(command_line[i] == '|')
      {
	index = 1;
	struct pipeline_command *nextcommand = malloc(sizeof(struct pipeline_command));
	for(int i = 0; i < MAX_ARGV_LENGTH; i++)
	  {
	    nextcommand->command_args[i] = NULL;
	  }
	nextcommand->next = NULL;
	nextcommand->redirect_in_path = NULL;
	nextcommand->redirect_out_path = NULL;
	current->next = nextcommand;
	current = nextcommand;
	i++;
      }
   else
      {
	char *args = malloc(MAX_ARGV_LENGTH);
	int j = 0;
	while(command_line[i] != ' ' && command_line[i] != '\n' && command_line[i] != '\t' && command_line[i] != '&' && command_line[i] != '>' && command_line[i] != '<' && command_line[i] != '|')
	  {
	    args[j] = command_line[i];
	    i++;
	    j++;
	  }
	if(current->command_args[0] == NULL)
	  current->command_args[0] = args;
	else
	  {
	    current->command_args[index] = args;
	    index++;
	  }
      }
    }
  return pipe;
}

void pipeline_free(struct pipeline *pipeline)
{
  struct pipeline_command *current = pipeline->commands; 
  while(current!=NULL)
    {
      for(int i = 0; i<MAX_ARGV_LENGTH; i++)
	{
	  free(current->command_args[i]); //free all the command arguments
	}
      free(current->redirect_in_path); 
      free(current->redirect_out_path);
      struct pipeline_command *next_command = current->next;
      free(current); //this frees the fields, redirects and next
      current = next_command; //move to the next one
    }
  free(pipeline); //free th whole pipelin

}

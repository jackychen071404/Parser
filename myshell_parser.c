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

  while(command_line[i]!='\0')
    {
      if(command_line[i] == ' ' || command_line[i] == '\n' || command_line[i] == '\t')
	i++;
}

void pipeline_free(struct pipeline *pipeline)
{


}

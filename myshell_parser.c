#include "myshell_parser.h"
#include "stddef.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void split_args(const char *input, char *output[MAX_ARGV_LENGTH], size_t *num_args) {
  char *split = strtok((char *)input, " \t\n"); //split string at \t and \n
  *num_args = 0;
  while (split != NULL && *num_args < MAX_ARGV_LENGTH) {
    output[(*num_args)++] = split; //num_args will be updated
    split  = strtok(NULL, " \t\n");
  }
}
    
struct pipeline *pipeline_build(const char *command_line)
{
  // TODO: Implement this function
  struct pipeline *pipe = malloc(sizeof(struct pipeline)); //allocate memory for a pipeline struct
  if (pipe == NULL) {
    perror("Error for allocation"); //print a failed message for failure to allocate memory
    exit(EXIT_FAILURE);
    }

  pipe->is_background = false;
  pipe->commands = NULL;

  size_t commands_count  = 0;
  char *commands[MAX_ARGV_LENGTH];
  split_args(command_line, commands, &commands_count);

  struct pipeline_command *current_command = NULL;

  for (size_t i = 0; i < commands_count; i++) {
    struct pipeline_command *command = malloc(sizeof(struct pipeline_command));
    if (command == NULL) {
      perror("Error for command");
      exit(EXIT_FAILURE);
    }
  }
  return NULL;
}

void pipeline_free(struct pipeline *pipeline)
{
  // TODO: Implement this function
}

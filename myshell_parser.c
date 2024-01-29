#include "myshell_parser.h"
#include "stddef.h"
#include <stdlib.h>
#include <stdio.h>

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

  return NULL;
}

void pipeline_free(struct pipeline *pipeline)
{
  // TODO: Implement this function
}

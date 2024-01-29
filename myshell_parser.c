#include "myshell_parser.h"
#include "stddef.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void split_args(const char *input, char *output[MAX_ARGV_LENGTH], size_t *num_args) {
  if (output == NULL || num_args == NULL ) {
    perror("Error: Output array is NULL");
    exit(EXIT_FAILURE);
  }

  char *copy = strdup(input);  // make a copy of the input string
  if (copy == NULL) {
    perror("Error allocating for string copy");
    exit(EXIT_FAILURE);
  }

  char *split = strtok(copy, " \t\n");
  *num_args = 0;
  
  while (split != NULL && *num_args < MAX_ARGV_LENGTH) {
    if (strlen(split) > 0) {
      output[(*num_args)++] = strdup(split);
    }
    split = strtok(NULL, " \t\n");
  }

  free(copy);
  for (size_t i = 0; i < *num_args; i++) {
  free(output[i]);  // Free each argument
  }
   output[*num_args] = NULL;
}
    
struct pipeline *pipeline_build(const char *command_line) {
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
    printf("Command[%zu]: %s\n", i, commands[i]);
   
    command->next = NULL;
    command->redirect_in_path = NULL;
    command->redirect_out_path = NULL;

    
    size_t num_args = 0;
    printf("Command[%zu]: %s\n", i, commands[i]);
    split_args(commands[i], command->command_args, &num_args);
    printf("Command[%zu]: %s\n", i, commands[i]);
    if (command->command_args == NULL) {
      perror("Error allocating memory for command arguments");
      exit(EXIT_FAILURE);
    }
    if (i == 0) {
      pipe->commands = command; //First command
    } else {
      current_command->next = command;
    }
    current_command = command;
  }
  return pipe;
}

void free_command(struct pipeline_command *command) {
  if (command == NULL) {
    return;
  }

  for (size_t i = 0; i < MAX_ARGV_LENGTH && command->command_args[i] != NULL; i++) {
    free(command->command_args[i]);
    command->command_args[i] = NULL;
  }

  free(command->command_args);
  free(command->redirect_in_path);
  free(command->redirect_out_path);
  free(command);
}

void pipeline_free(struct pipeline *pipeline)
{
  if (pipeline == NULL) {
    return;
  }

  struct pipeline_command *current = pipeline->commands;
  while (current != NULL) {
    struct pipeline_command *next = current->next;
    //deallocate elements
    free_command(current);
    current = next;
  }

  free(pipeline); //deallocate all memory of pipeline after deallocate its elements
  // TODO: Implement this function
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define DELIMITER " \t\r\n\a"

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

char *builtin_commands[] = {"cd", "help", "exit"};
int (builtin_functions[]) (char *) = {&shell_cd, &shell_help, &shell_exit};

int shell_num_builtins() { return sizeof(builtin_commands) / sizeof(char *); }

int shell_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "shell: expected argument to \"cd\"\n");
  } else if (chdir(args[1]) != 0) {
    perror("shell");
  }
  return 1;
}

int shell_help(char **args) {
  printf("Simple Shell 0.1+\n");
  printf("The following commands are built in:\n");

  for (int i = 0; i < shell_num_builtins(); i++) {
    printf("  %s\n", builtin_commands[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int shell_exit(char **args) { return 0; }

int shell_execute(char **args) {
  if (args[0] == NULL) {
    return 1;
  }

  for (int i = 0; i < shell_num_builtins(); i++) {
    if (strcmp(args[0], builtin_commands[i]) == 0) {
      return (*builtin_functions[i])(args);
    }
  }

  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("shell");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("shell");
  } else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

char *read_input_line(void) {
  char *line = NULL;
  size_t buffer_size = 0;
  getline(&line, &buffer_size, stdin);
  return line;
}

char **split_input_line(char *line) {
  int buffer_size = BUFFER_SIZE, i = 0;
  char **tokens = malloc(buffer_size * sizeof(char *));
  char *token;

  if (!tokens) {
    fprintf(stderr, "shell: allocation error\n");

    exit(EXIT_FAILURE);
  }

  token = strtok(line, DELIMITER);

  while (token != NULL) {
    tokens[i] = token;
    i++;

    if (i >= buffer_size) {
      buffer_size += BUFFER_SIZE;
      tokens = realloc(tokens, buffer_size * sizeof(char *));
      if (!tokens) {
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, DELIMITER);
  }

  tokens[i] = NULL;
  return tokens;
}

void shell_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = read_input_line();
    args = split_input_line(line);
    status = shell_execute(args);

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char **argv) {
  shell_loop();
  return EXIT_SUCCESS;
}

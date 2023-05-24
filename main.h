#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
void init_shell(void);
char **read_line(char **buffer);
int exec_child_proc(char *argv[]);
int _strcmp(char *s1, char *s2);
int num_of_substr(char *str, char *delimiter);
char *_strtok(char *str, const char *delimiter);
char **str_split(char *str, char *delimiter);
int exec_built_in(char *argv[]);
int str_to_int(char *num);
char *search_env(char *keyword);
char **path(void);
int find_file(void);
#endif

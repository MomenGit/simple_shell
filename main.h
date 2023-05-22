#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int init_shell(void);
int exec_child_proc(char *argv[]);
int _strcmp(char *s1, char *s2);
int num_of_substr(char *str, char delimiter);
char *str_split(char *str, char delimiter);
#endif

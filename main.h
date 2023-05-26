#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include "str_ops.h"
#include "lists.h"

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char *
	*environ;

/**
 * struct shell_t - contains pseudo-arguments to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct shell_t
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;	  /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} shell_vars;

/**
 * Initializes a Shell_vars struct without memory allocation
 */
#define INIT_SHELL_VARS                                                         \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 * struct builtin - contains a builtin string and related function
 * @cmd: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *cmd;
	int (*func)(shell_vars *);
} builtin_t;
/**/
int shell_init(shell_vars *shell_vs, char **argv);
int interactive(shell_vars *shell_vs);
int find_builtin(shell_vars *shell_vs);
void fork_cmd(shell_vars *shell_vs);
void find_cmd(shell_vars *sh_vs);

int is_delim(char c, char *delim);
int _isalpha(int c);

int is_chain(shell_vars *, char *, size_t *);
void check_chain(shell_vars *, char *, size_t *, size_t, size_t);
int replace_alias(shell_vars *);
int replace_vars(shell_vars *);
int replace_string(char **, char *);

ssize_t input_buf(shell_vars *shell_vs, char **buf, size_t *len);
ssize_t get_input(shell_vars *shell_vs);
ssize_t read_buf(shell_vars *shell_vs, char *buf, size_t *i);
int _getline(shell_vars *shell_vs, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused)) int sig_num);

void print_error(shell_vars *shell_vs, char *estr);
int _erratoi(char *s);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

void clear_vars(shell_vars *shell_vs);
void set_vars(shell_vars *shell_vs, char **av);
void free_vars(shell_vars *shell_vs, int all);

int _env(shell_vars *shell_vs);
char *_getenv(shell_vars *shell_vs, const char *name);
int _set_env(shell_vars *shell_vs);
int _unset_env(shell_vars *shell_vs);
int set_env_list(shell_vars *shell_vs);
char **get_environ(shell_vars *shell_vs);
int _unsetenv(shell_vars *shell_vs, char *var);
int _setenv(shell_vars *shell_vs, char *var, char *value);

int _cd(shell_vars *shell_vs);
int _exiting(shell_vars *shell_vs);
int _help(shell_vars *shell_vs);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void ffree(char **pp);
char *_memset(char *s, char b, unsigned int n);
int bfree(void **ptr);

int is_cmd(shell_vars *shell_vs, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(shell_vars *shell_vs, char *pathstr, char *cmd);

char *get_history_file(shell_vars *shell_vs);
int write_history(shell_vars *shell_vs);
int read_history(shell_vars *shell_vs);
int build_history_list(shell_vars *shell_vs, char *buf, int linecount);
int renumber_history(shell_vars *shell_vs);
int _history(shell_vars *);

int _alias(shell_vars *);
int print_alias(list_t *node);
int set_alias(shell_vars *shell_vs, char *str);
int unset_alias(shell_vars *shell_vs, char *str);
#endif

#include "main.h"

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @shell_vs: the parameter & return shell_vs structs
 * Return: void
 */
void fork_cmd(shell_vars *shell_vs)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(shell_vs->path, shell_vs->argv, get_environ(shell_vs)) == -1)
		{
			free_vars(shell_vs, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(shell_vs->status));
		if (WIFEXITED(shell_vs->status))
		{
			shell_vs->status = WEXITSTATUS(shell_vs->status);
			if (shell_vs->status == 126)
				print_error(shell_vs, "Permission denied\n");
		}
	}
}

/**
 * find_cmd - finds a command in PATH
 * @sh_vs: the parameter & return shell_vs struct
 * Return: void
 */
void find_cmd(shell_vars *sh_vs)
{
	char *path = NULL;
	int i, k;

	sh_vs->path = sh_vs->argv[0];
	if (sh_vs->linecount_flag == 1)
	{
		sh_vs->line_count++;
		sh_vs->linecount_flag = 0;
	}
	for (i = 0, k = 0; sh_vs->arg[i]; i++)
		if (!is_delim(sh_vs->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_path(sh_vs, _getenv(sh_vs, "PATH="), sh_vs->argv[0]);
	if (path)
	{
		sh_vs->path = path;
		fork_cmd(sh_vs);
	}
	else
	{
		int bool1 = (interactive(sh_vs) || _getenv(sh_vs, "PATH="));

		if ((bool1 || sh_vs->argv[0][0] == '/') && is_cmd(sh_vs, sh_vs->argv[0]))
			fork_cmd(sh_vs);
		else if (*(sh_vs->arg) != '\n')
		{
			sh_vs->status = 127;
			print_error(sh_vs, "not found\n");
		}
	}
}

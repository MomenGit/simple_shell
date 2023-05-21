#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	char command[100];

	while (1)
	{
		printf("$ ");

		char *token;
		char *argv[100];
		int argc = 0;

		fgets(command, sizeof(command), stdin);
		token = strtok(command, " \n");

		while (token != NULL)
		{
			argv[argc++] = token;
			token = strtok(NULL, " \n");
		}

		argv[argc] = NULL;

		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork failed");
			exit(1);
		}
		else if (pid == 0)
		{
			if (execvp(argv[0], argv) == -1)
			{
				perror("execvp failed");
				exit(1);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}

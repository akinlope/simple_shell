#include "main.h"
/**
 * shell - Runs a Shell comand
 *
 * Return: 0 on success.
*/
int shell(void)
{
	int i = 0, status;
	pid_t pid;
	size_t n;
	char *buff, *words, *delim, *argv[] = {"bin", NULL};

	delim = " \n\t\r";

	while (1)
	{
		printf("#cisfun$ ");
		if (getline(&buff, &n, stdin) == -1)
			break;

		words = _strtok(buff, delim);
		while (words)
		{
			*(argv + i) = words;
			words = _strtok(NULL, delim);
		}
		*(argv + (i + 1)) = NULL;

		pid = fork();
		if (pid == -1) /*check if Fork fails*/
			return (-1);

		if (pid == 0) /*the child proccess which we need to run first*/
		{
			execute(argv[0], argv);
		}
		if (pid > 0)
		{
			wait(&status);
			/**
			 * the father process that we want to
			 * wait for the child to complete b4 it runs
			 */
		}
	}
	free(buff);
	exit(status);
	return (0);
}

/**
 * execute - Calls the execve function
 *
 * @pathname: the argv[0]
 * @argv: the while arg vector
 *
 * Return: 0 on success.
*/

int execute(char *pathname, char *argv[])
{
	int val;

	val = execve(pathname, argv, environ);
	if (val == -1)
	{
		perror("./shell");
		exit(EXIT_FAILURE);
	}

	return (0);
}

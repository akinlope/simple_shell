#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t child;
    char *command[16], *tok, *lineptr = NULL; // Not going to use commands with more than 15 words; extra room for NULL term
    size_t i, n; // Number of bytes read into lineptr (mallocated internally by getline)
    int status;

    while (1)
    {
      printf("$ ");
      if (getline(&lineptr, &n, stdin) == -1)
          break;
      tok = strtok(lineptr, " \t\n\r"); // First call to strtok stores the line in a static variable; second arg is delimiters
      for (i = 0; i < 16 && tok != NULL; i++) // strtok returns NULL once there are no more tokens
      {
          command[i] = tok;
          tok = strtok(NULL, " \t\n\r");
      }
      command[i] = NULL; // `execve' expects a NULL terminator from both the command and the environment; this assumes i < 15...
      child = fork();
      if (child == 0) // No error checking; too close to being not a "snippet"
      {
          if (execve(command[0], command, envp))
          {
              perror("execve");
              exit(EXIT_FAILURE);
          }
      }
      if (child > 0) // Successful forks return positive process id's the parent
         wait(&status);
    }
    putchar('\n');
    free(lineptr);
    exit(status);
}
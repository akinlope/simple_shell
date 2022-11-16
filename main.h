#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
extern char **environ;


int execute(char *pathname, char *argv[]);
int shell(void);
char *_strtok(char str[], const char *delim);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
#endif

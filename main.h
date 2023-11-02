#ifndef MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


char *exec_cmd(char **args, char **env);
void print_env(char **env);
extern char **environ;

#endif

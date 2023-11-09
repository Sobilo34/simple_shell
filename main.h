#ifndef MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stddef.h>

#define PATH_MAX 4096
#define MAX_ALIASES 100

void exec_cmd(char **args, char **env);
void print_env(char **env);
extern char **environ;
int check_cmd(char **input);
ssize_t gb_getline(char **line_ptr, size_t *len_siz, FILE *stream);
size_t gb_strlen(const char *input);
int gb_strcmp(const char *str1, const char *str2);
char *gb_strcat(char *str1, const char *str2);
char *gb_strcpy(char *dest, const char *scr);
void error_prt(char *cmd, char *name);
char *gb_strtok(char *str, const char *delim);
char *gb_strdup(const char *input);
int change_curr_dir(char **args);
int execute_command(char **args, char **env, int success);
int split_commands(char *input, char *commands[]);
void print_alias(char *name);
void handle_alias_command(char **args);
void define_alias(char *name, char *value);

extern char **environ;



typedef struct Alias
{
	char *name;
	char *value;
} Alias;

Alias aliases[MAX_ALIASES];


#endif

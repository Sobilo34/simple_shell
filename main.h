#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/stat.h>

#define PATH_MAX 4096
#define ALIAS_MAX 100

void exec_cmd(char **args, char **env);
void print_env(char **env);
extern char **environ;
int check_cmd(char **input);
ssize_t gb_getline(char **line_ptr, size_t *len_siz, FILE *stream);
size_t gb_strlen(const char *input);
void ret_error(const char *arg, int line);
int gb_strcmp(const char *str1, const char *str2);
char *gb_strcat(char *str1, const char *str2);
char *gb_strcpy(char *dest, const char *scr);
void error_prt(char *cmd, char *name);
char *gb_strtok(char *str, const char *delim);
char *gb_strdup(const char *input);
void gb_print(const char *format, ...);
int gb_setenv(const char *variable, const char *value, char ***env);
int gb_unsetenv(const char *variable, char ***env);
int gb_strstartswith(const char *str, const char *prefix);
int change_curr_dir(char **args);
int exec_with_operator(char **args, char **env, int success);
int split_cmds(char *input, char *cmd[]);
void prt_alias(char *name);
void handle_alias(char **args);
void define_alias(char *name, char *value);
char *replacer(const char *input, const char *prev, const char *present);
char *replace_implement(char *cmd, int stat, int pid);
void itoa(int num, char *str);

/*int gb_getline(char **lineptr, size_t *n, FILE *stream);*/

typedef struct Alias
{
	char *name;
	char *value;
} Alias;

Alias aliases[ALIAS_MAX];


#endif

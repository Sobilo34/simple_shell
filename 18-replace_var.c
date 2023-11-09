#include "main.h"

/**
 * replace_var - This is the unctio that replace $?, $$, and other variables
 * @cmd: The command
 * @stat: THe wait status
 * @paid: THe child process
 *
 */

char *replace_var(char *cmd, int stat, int pid) 

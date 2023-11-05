#include "main.h"

/**
 * error_prt - This is a funcion that is used to print error
 * @cmd: The command to write an error on
 * @name: The name of the program
 */

void error_prt(char *cmd, char *name)
{
    char *error1, *error2;
    size_t err1_len, err2_len;
    
    error1 = "No such file";
    error2 = " or directory\n";
    err1_len = gb_strlen(error1);
    err2_len = gb_strlen(error2);
    write(STDERR_FILENO, name, gb_strlen(name));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, cmd, gb_strlen(cmd));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, error1, err1_len);
    write(STDERR_FILENO, error2, err2_len);
}

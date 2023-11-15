#include "main.h"
char *replace_implement(char *cmd, int stat, int pid);

/**
 * int_to_str : function that converts integer to string.
 * @num: int to be converted
 * @str:  string thats been converted
 */
void int_to_str(int num, char *str)
{
	snprintf(str, 32, "%d", num);
}
/**
 * replacer : This is the function that replace variable
 * @input: the variable to be replaced
 * @prev: old variable
 * @present: new variable
 * Return: 1 if replaced, 0 if not.
 */
char *replacer(const char *input, const char *prev, const char *present)
{
	int a, count = 0;
	int prev_len = gb_strlen(prev), present_len = gb_strlen(present);
	char *output;

	for (a = 0; input[a] != '\0'; a++)
	{
		if (strstr(&input[a], prev) == &input[a])
		{
			++count;
			a += prev_len - 1;
		}
	}

	output = (char *)malloc(a + count * (present_len - prev_len) + 1);

	a = 0;
	while (*input)
	{
		if (strstr(input, prev) == input)
		{
			gb_strcpy(&output[a], present);
			a += present_len;
			input += prev_len;
		}

		else
			output[a++] = *input;
	}

	output[a] = '\0';
	return (output);
}

/**
 * replace_implement - This is the unctio that replace $?,
 * $$, and other variables
 * @cmd: The command
 * @stat: THe wait status
 * @pid: THe child process
 * Return: reyurns 1 on sucess, 0 if otherwise
 */

char *replace_implement(char *cmd, int stat, int pid)
{
	int a, len, output_len;
	char *output, input_stat[32], input_pid[32];

	len = gb_strlen(cmd);
	output_len = len + 30;
	output = (char *)malloc(output_len);

	if (output == NULL)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	output[0] = '\0';

	if (gb_strcmp(cmd, "&&") != 0 && gb_strcmp(cmd, "||") != 0)
	{
		for (a = 0; a < len; a++)
		{
			if (cmd[a] == '$' && cmd[a + 1] == '?')
			{
				int_to_str(stat, input_stat);
				strcat(output, input_stat);
				a++;
			}

			else if (cmd[a] == '$' && cmd[a + 1] == '$')
			{
				int_to_str(pid, input_pid);
				strcat(output, input_pid);
				a++;
			}

			else
			{
				/**output = strncat(output, &cmd[a], 1);**/
				*output++ = cmd[a];
				*output = '\0';
			}
		}
	}

	else
	{
		gb_strcpy(output, cmd);
	}

	printf("%s\n", output);

	return (output);
}


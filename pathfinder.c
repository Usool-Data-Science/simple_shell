#include <stdio.h>
#include "shell.h"

/**
  * pathfinder - A function that finds absolute path of a command in PAHT
  *
  * @filename: The command name to find in the PATH.
  * Return: The absolute address of the command or NULL.
  */

char *pathfinder(char *filename)
{
	char *path_copy, *path_env;
	char *token, *delim = ":";
	char *absolute_path;
	size_t tok_len, file_len;

	/*If the filename is accessible, use it as is*/
	if (access(filename, F_OK) == 0)
	{
		return (filename);
	}
	else
	{
		path_env = getenv("PATH");
		path_copy = strdup(path_env); /*FREE ME !!!!*/

		token = strtok(path_copy, delim);
		while (token)
		{
			/*write the full path inside a string */
			/*we can use it like a buffer too and use write*/
			tok_len = strlen(token);
			file_len = strlen(filename);
			absolute_path = (char *)malloc(tok_len + file_len + 2);
			if (absolute_path == NULL)
			{
				perror("Error");
				free(path_copy);
				return ("");
			}
			sprintf(absolute_path, "%s/%s", token, filename);
			if (access(absolute_path, F_OK) == 0)
			{
				free(path_copy);
				return (absolute_path);
			}
			token =  strtok(NULL, delim);
		}
	}
	return ("");
}

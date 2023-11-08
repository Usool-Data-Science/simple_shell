#include "shell.h"

/**
 * print_alias - add, remove or show aliases
 * @data: struct for the pogram's data
 * @alias: name of the alias to be printed
 * Return: 0 if success, or other number if its declared in the argument
 */
int print_alias(data_of_program *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->alias_list[i], alias, alias_length)
				&&      data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, rremove or show aliases
 * @data:  struct for the program's data
 * @name: name of the requested alias
 * Return: zero if success, or other number if its declared in the arguments
 */
char *get_alias(data_of_program *data, char *name)
{
	int i, alias_length;

	/*validate the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{/* iterates through the environ and checks for coincidence of the varname */
		if (str_compare(name, data->alias_list[i], alias_length) &&
				data->alias_list[i][alias_length] == '=')
		{/* returns the value of the key NAME= when find it */
			return (data->alias_list[i] + alias_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias -add, or override alias
 * @alias_string: alias to be seated in this form (name='value')
 * @data: struct for the program's data
 * Return: 0 if success, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *tmp = NULL;

	/* validate the arguments */
	if (alias_string == NULL || data->alias_list == NULL)
		return (1);
	/* Iterates alias to find =  char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* search if the value of the alias is another alias */
			tmp = get_alias(data, alias_string + i + 1);
			break;
		}
	/*iterates through the alias list and check for coincidence of the varname*/
	for (j = 0; data->alias_list[j]; j++)
		if (str_compare(buffer, data->alias_list[j], i) &&
				data->alias_list[j][i] == '=')
		{/* if the alias already exist */
			free(data->alias_list[j]);
			break;
		}
	/* add the alias */
	if (tmp)
	{/* if the alias already exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, tmp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else /* if the alias does not exisr */
		data->alias_list[j] = str_duplicate(alias_string);
	return (0);
}

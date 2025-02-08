/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:19:42 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/08 14:47:37 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Gets a value from its index
*/
char	*env_value_from_index(int pos, char **env_vars)
{
	char	*var;
	char	**split;
	char	*result;

	result = NULL;
	var = env_vars[pos];
	split = ft_split(var, '=');
	if (2 == count_array(split))
	{
		if (!(2 == ft_strlen(split[1]) && 0 == ft_strncmp("''", split[1], 2)))
			result = ft_strdup(split[1]);
	}
	free_stringlist(split);
	return (result);
}

/*
	Gets one line from env_vars, excluding the name= part
*/
char	*env_value(char *var_name, char **env_vars)
{
	char	*var;

	var = env_var(var_name, env_vars);
	if (!var)
		return (NULL);
	return (ft_substr(var, ft_strlen(var_name) + 1, ft_strlen(var)));
}

/*
	Returns the array index of the variable
*/
int	env_var_index(char *var_name, char **env_var)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(var_name);
	while (env_var[++i])
		if (0 == ft_strncmp(var_name, env_var[i], len)
			&& '=' == env_var[i][len])
			return (i);
	return (-1);
}

/*
	Gets one line from env_vars, including the name= part
*/
char	*env_var(char *var_name, char **env_vars)
{
	int	pos;

	pos = env_var_index(var_name, env_vars);
	if (-1 == pos)
		return (NULL);
	return (env_vars[pos]);
}

/*
	Counts the elements in the array.
	Used by env_vars and cmd.cmd
*/
int	count_array(char **array)
{
	int	count;

	if (!array)
		return (0);
	count = -1;
	while (array[++count])
		;
	return (count);
}

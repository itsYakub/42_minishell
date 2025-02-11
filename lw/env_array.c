/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:19:42 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/11 13:30:01 by lwillis          ###   ########.fr       */
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
	Appends to a string, freeing the old one
*/
static char	*join_and_free(char *old, char *new)
{
	char	*tmp;

	if (!old)
		old = ft_strdup("");
	tmp = ft_strjoin(old, new);
	free(new);
	free(old);
	return (tmp);
}

/*
	Gets one line from env_vars, excluding the name= part.
	Also adds any non-alpha characters after the var
*/
static char	*single_env_value(char *var_name, char **env_vars)
{
	char	*var;
	char	*sub1;
	char	*sub2;
	int		i;

	i = 0;
	while (var_name[i] && (ft_isalnum(var_name[i]) || '_' == var_name[i]))
		i++;
	sub1 = ft_substr(var_name, 0, i);
	var = env_var(sub1, env_vars);
	if (!var)
	{
		free(sub1);
		return (NULL);
	}
	sub2 = ft_substr(var, ft_strlen(sub1) + 1, ft_strlen(var));
	free(sub1);
	if (i < ft_strlen(var_name))
	{
		sub1 = join_and_free(sub2, ft_substr(var_name, i, ft_strlen(var_name)));
		return (sub1);
	}
	return (sub2);
}

/*
	Replaces vars in one block of text
*/
char	*env_value(char *var_name, t_mini *mini)
{
	char	**split;
	int		i;
	char	*out;

	out = NULL;
	split = ft_split(var_name, '$');
	i = 0;
	while (i < count_array(split))
	{
		if (0 == ft_strcmp("?", split[i]))
			out = join_and_free(out, ft_itoa(mini->exitcode));
		else
			out = join_and_free(out, single_env_value(split[i], mini->env));
		i++;
	}
	free_stringlist(split);
	return (out);
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

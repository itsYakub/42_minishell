/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:19:42 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 13:41:09 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_value(char *var, int start)
{
	char	*sub;

	sub = ft_substr(var, start, ft_strlen(var));
	return (sub);
}

/*
	Checks whether a variable name exists and is set
*/
int	empty_var(char *var_name, char **env_vars)
{
	char	*var;
	char	*sub;

	var = env_var(var_name, env_vars);
	if (!var)
		return (1);
	
	sub = var_value(var, ft_strlen(var_name));
	printf("%s\n", sub);
	return (0);
}

/*
	Returns the array index of the variable
*/
int	env_var_pos(char *var_name, char **env_var)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(var_name);
	while (env_var[++i])
		if (0 == ft_strncmp(var_name, env_var[i], len))
			return (i);
	return (-1);
}

/*
	
*/

char	*env_var(char *var_name, char **env_vars)
{
	int	pos;

	pos = env_var_pos(var_name, env_vars);
	if (-1 == pos)
		return (NULL);
	return (env_vars[pos]);
}

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

void	copy_env_array(char *old[], char **new[])
{
	int	i;
	int	count;

	count = count_array(old);
	i = -1;
	while (++i < count)
		(*new)[i] = ft_strdup(old[i]);
	(*new)[count + 1] = NULL;
}

char	**init_env_array(char *envp[])
{
	char	**env_vars;
	int		count;

	count = count_array(envp);
	env_vars = malloc(sizeof(char *) * (count + 1));
	if (!env_vars)
		return (NULL);
	copy_env_array(envp, &env_vars);
	return (env_vars);
}

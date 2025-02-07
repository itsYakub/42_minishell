/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:19:42 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 16:52:25 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	Checks whether a variable name exists and is set
*/
int	empty_var(char *var_name, char **env_vars)
{
	char	*var;

	var = env_value(var_name, env_vars);
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
		if (0 == ft_strncmp(var_name, env_var[i], len) && '=' == env_var[i][len])
			return (i);
	return (-1);
}

/*
	Gets one line from env_vars, including the name= part
*/
char	*env_var(char *var_name, char **env_vars)
{
	int	pos;

	pos = env_var_pos(var_name, env_vars);
	if (-1 == pos)
		return (NULL);
	return (env_vars[pos]);
}

void	free_stringlist(char **env_vars)
{
	int	i;

	i = -1;
	while (env_vars[++i])
		free(env_vars[i]);
	free(env_vars);
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

void	copy_env_array(char **original, char ***copy)
{
	int	i;
	
	i = -1;
	while (original[++i])
		(*copy)[i] = ft_strdup(original[i]);
}

/*
	Creates a copy of the env vars so it can be freed later
*/
char	**init_env_array(char **envp)
{
	char	**env_vars;
	int		count;

	count = count_array(envp);
	count++;
	env_vars = malloc(sizeof(char *) * count);
	if (!env_vars)
		return (NULL);
	copy_env_array(envp, &env_vars);	
	env_vars[count] = NULL;
	return (env_vars);
}

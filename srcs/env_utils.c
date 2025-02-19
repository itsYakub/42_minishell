/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:29:21 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/19 11:07:37 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Counts the elements in the array
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

/*
	Copies the list of env vars to a new list, at the start or when adding
*/
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
	int		pos;
	char	*pwd;

	count = count_array(envp);
	env_vars = malloc(sizeof(char *) * (count + 1));
	if (!env_vars)
		return (NULL);
	copy_env_array(envp, &env_vars);
	env_vars[count] = NULL;
	pos = env_var_index("OLDPWD", env_vars);
	free(env_vars[pos]);
	pwd = getcwd(NULL, 0);
	env_vars[pos] = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	return (env_vars);
}

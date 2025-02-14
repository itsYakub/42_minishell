/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:41:52 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/14 15:00:34 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_stringlist(char **env_vars)
{
	int	i;

	i = -1;
	while (env_vars[++i])
		free(env_vars[i]);
	free(env_vars);
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
	env_vars = malloc(sizeof(char *) * (count + 1));
	if (!env_vars)
		return (NULL);
	copy_env_array(envp, &env_vars);
	env_vars[count] = NULL;
	return (env_vars);
}

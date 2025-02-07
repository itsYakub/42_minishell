/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:19:42 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 10:44:00 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		(*new)[i] = old[i];
}

char	**init_env_array(char *envp[])
{
	char	**new_envp;
	int		count;

	count = count_array(envp);
	new_envp = malloc(sizeof(char *) * (count));
	copy_env_array(envp, &new_envp);
	return (new_envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:36:31 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/18 12:36:46 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*make_path(char *command, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = lw_strjoin(path, "/");
	tmp2 = lw_strjoin(tmp, command);
	free(tmp);
	if (0 == access(tmp2, F_OK | X_OK))
		return (tmp2);
	free(tmp2);
	return (NULL);
}

static char	*extract_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (0 == lw_strncmp("PATH", envp[i], 4))
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

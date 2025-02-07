/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-utilpath.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:38:28 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/07 11:26:25 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*__msh_creaturl(char *s1, char *s2);
static char	**__msh_creatpths(char *var, char *util, size_t off);

char	*msh_getutil(t_mini *mini, char **util)
{
	char	**paths;
	char	*var;
	int		i;

	var = msh_getenv(mini, "PATH");
	if (var)
	{
		paths = __msh_creatpths(var, *util, 5);
		if (!paths)
			return (*util);
		i = -1;
		while (paths[++i])
		{
			if (!access(paths[i], X_OK))
			{
				free(*util);
				*util = ft_strdup(paths[i]);
				ft_free2d((void **) paths);
				return (*util);
			}
		}
		ft_free2d((void **) paths);
	}
	return (*util);
}

static char	*__msh_creaturl(char *s1, char *s2)
{
	char	*cmd0;
	char	*cmd1;

	cmd0 = NULL;
	cmd1 = NULL;
	cmd0 = ft_strjoin(s1, "/");
	cmd1 = ft_strjoin(cmd0, s2);
	free(cmd0);
	return (cmd1);
}

static char	**__msh_creatpths(char *var, char *util, size_t off)
{
	char	**paths;
	size_t	iter;

	paths = ft_split(var + off, ':');
	free(var);
	if (!paths)
		return (NULL);
	iter = -1;
	while (paths[++iter])
		paths[iter] = __msh_creaturl(paths[iter], util);
	return (paths);
}


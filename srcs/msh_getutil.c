/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getutil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:38:28 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/21 14:09:19 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*__msh_creaturl(char *s1, char *s2);
static char	**__msh_creatpths(char *var, char *util, size_t off);

/*
	Handles multiple output redirection, but only the last one gets written to
*/
int	handle_other_filenames(t_command *cmd)
{
	char	**split;
	int		i;
	int		output_fd;

	if (cmd->other_outnames)
	{
		split = ft_split(cmd->other_outnames, '\n');
		i = -1;
		while (++i < count_array(split) - 1)
		{
			output_fd = open(split[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (output_fd < 0)
			{
				print_error(split[i]);
				ft_free2d((void **) split);
				return (0);
			}
			close(output_fd);
		}
	}
	return (1);
}

char	*msh_getutil(t_mini *mini, char **util)
{
	char	**paths;
	char	*var;
	int		i;

	var = env_value("PATH", mini, 0);
	if (var)
	{
		paths = __msh_creatpths(var, *util, 5);
		free(var);
		if (!paths)
			return (*util);
		i = -1;
		while (paths[++i])
		{
			if (!access(paths[i], F_OK | X_OK))
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
	char	*tmp;
	size_t	iter;

	paths = ft_split(var + off, ':');
	if (!paths)
		return (NULL);
	iter = -1;
	while (paths[++iter])
	{
		tmp = ft_strdup(paths[iter]);
		free(paths[iter]);
		paths[iter] = __msh_creaturl(tmp, util);
		free(tmp);
	}
	return (paths);
}

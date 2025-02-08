/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:08:22 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/08 08:13:36 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"
#include "../minishell.h"

void	show_error(char *error, int error_code)
{
	write(2, error, ft_strlen(error));
	if (0 != error_code)
		exit (error_code);
}

static char	*make_path(char *command, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path, "/");
	tmp2 = ft_strjoin(tmp, command);
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
		if (0 == ft_strncmp("PATH", envp[i], 4))
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

int	do_cmd(t_cmd cmd, char *envp[])
{
	char	**split_path;
	char	*path;
	char	*tmp_path;
	int		i;

	path = extract_path(envp);
	if (!path)
		show_error("PATH not found!\n", 1);
	if (0 == access(cmd.cmd[0], F_OK | X_OK))
		return (execve(cmd.cmd[0], cmd.cmd, envp));
	i = 0;
	split_path = ft_split(path, ':');
	while (split_path[i])
	{
		tmp_path = make_path(cmd.cmd[0], split_path[i]);
		if (tmp_path)
			return (execve(tmp_path, cmd.cmd, envp));
		i++;
	}
	ft_free2d((void **) split_path);
	show_error("command not found\n", 127);
	return (1);
}

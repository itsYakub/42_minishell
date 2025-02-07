/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:08:22 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 17:41:11 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"

void	show_error(char *error, int error_code)
{
	write(2, error, ft_strlen(error));
	if (0 != error_code)
		exit (error_code);
}

static void	free_split(char **split_str)
{
	int	i;

	i = 0;
	while (split_str[i])
		free(split_str[i++]);
	free(split_str);
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

int	do_cmd(char *cmd, char *envp[])
{
	char	**split_cmd;
	char	**split_path;
	char	*path;
	char	*tmp_path;
	int		i;

	path = extract_path(envp);
	if (!path)
		show_error("PATH not found!\n", 1);
	split_cmd = ft_split(cmd, ' ');
	if (0 == access(split_cmd[0], F_OK | X_OK))
		return (execve(split_cmd[0], split_cmd, envp));
	i = 0;
	split_path = ft_split(path, ':');
	while (split_path[i])
	{
		tmp_path = make_path(split_cmd[0], split_path[i]);
		if (tmp_path)
			return (execve(tmp_path, split_cmd, envp));
		i++;
	}
	free_split(split_cmd);
	free_split(split_path);
	show_error("command not found\n", 127);
	return (1);
}

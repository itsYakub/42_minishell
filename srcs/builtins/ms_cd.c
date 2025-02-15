/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:22:21 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/15 14:55:05 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd(t_command *cmd)
{
	int	pos;

	pos = env_var_index("PWD", cmd->mini->env);
	free(cmd->mini->env[pos]);
	cmd->mini->env[pos] = ft_strjoin("PWD=", getcwd(NULL, 0));
}

void	ms_cd(t_command *cmd)
{
	char	*path;
	int		pos;

	if (count_array(cmd->args) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	pos = env_var_index("OLDPWD", cmd->mini->env);
	free(cmd->mini->env[pos]);
	cmd->mini->env[pos] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (!cmd->args[1])
	{
		path = env_value("HOME", cmd->mini, 0);
		chdir(path);
		update_pwd(cmd);
		free(path);
	}
	else
	{
		chdir(cmd->args[1]);
		update_pwd(cmd);
	}
}

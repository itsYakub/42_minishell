/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:22:21 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/08 12:25:03 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_pwd(t_cmd *cmd)
{
	int	pos;

	pos = env_var_index("PWD", cmd->mini->env);
	free(cmd->mini->env[pos]);
	cmd->mini->env[pos] = ft_strjoin("PWD=", getcwd(NULL, 0));
}

void	ms_cd(t_cmd *cmd)
{
	char	*path;
	int		pos;

	pos = env_var_index("OLDPWD", cmd->mini->env);
	free(cmd->mini->env[pos]);
	cmd->mini->env[pos] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (!cmd->cmd[1])
	{
		path = env_value("HOME", cmd->mini->env);
		chdir(path);
		update_pwd(cmd);
		free(path);
	}
	else
	{
		chdir(cmd->cmd[1]);
		update_pwd(cmd);
	}
}

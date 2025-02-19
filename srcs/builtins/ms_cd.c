/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:22:21 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/19 09:30:49 by lwillis          ###   ########.fr       */
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

static void	set_dir(t_command *cmd)
{
	int	code;

	code = chdir(cmd->args[1]);
	if (0 == code)
		update_pwd(cmd);
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		cmd->mini->exitcode = 1;
		return ;
	}
	cmd->mini->exitcode = 0;
}

void	ms_cd(t_command *cmd)
{
	char	*path;
	int		pos;

	if (count_array(cmd->args) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		cmd->mini->exitcode = 1;
		return ;
	}
	pos = env_var_index("OLDPWD", cmd->mini->env);
	free(cmd->mini->env[pos]);
	cmd->mini->env[pos] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (!cmd->args[1])
	{
		path = env_value("HOME", cmd->mini, 0);
		chdir(path);
		free(path);
		cmd->mini->exitcode = 0;
		return ;
	}
	else
		set_dir(cmd);
}

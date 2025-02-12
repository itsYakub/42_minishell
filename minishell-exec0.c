/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-exec0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:01:35 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/12 08:29:27 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_exec(t_mini *mini)
{
	size_t	iter;

	if (mini->cmdc)
	{
		iter = -1;
		while (++iter < (size_t) mini->cmdc - 1)
			msh_exec_pipe(&mini->cmd[iter]);
		msh_exec_util(&mini->cmd[iter]);
	}
	return (1);
}

int	msh_exec_pipe(t_cmd *cmd)
{
	int	pid;
	int	p_fd[2];

	if (-1 == pipe(p_fd))
		return (printf("minishell: %s\n", strerror(errno)));
	pid = fork();
	if (-1 == pid)
		return (printf("minishell: %s\n", strerror(errno)));
	if (0 == pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		msh_exec_util(cmd);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
	return (1);
}

int	msh_exec_util(t_cmd *cmd)
{
	int	pid;
	
	if (msh_isbuiltin(cmd))
		return (msh_exec_builtin(cmd));
	pid = fork();
	if (!pid)
	{
		cmd->args[0] = msh_getutil(cmd->mini, cmd->args);
		if (execve(cmd->args[0], cmd->args, cmd->mini->env))
			exit(printf("minishell: %s\n", strerror(errno)));
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, &cmd->mini->exitcode, 0);
	return (1);
}

int	msh_exec_builtin(t_cmd *cmd)
{
	if (cmd_equals("pwd", cmd->args[0]))
		ms_pwd(cmd);
	if (cmd_equals("cd", cmd->args[0]))
		ms_cd(cmd);
	if (cmd_equals("exit", cmd->args[0]))
		ms_exit(cmd);
	if (cmd_equals("env", cmd->args[0]))
		ms_env(cmd);
	if (cmd_equals("export", cmd->args[0]))
		ms_export(cmd);
	if (cmd_equals("echo", cmd->args[0]))
		ms_echo(cmd);
	if (cmd_equals("unset", cmd->args[0]))
		ms_unset(cmd);
	return (1);
}

int	msh_isbuiltin(t_cmd *cmd)
{
	return (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0]))
	);
}

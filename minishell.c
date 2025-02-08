/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/08 14:46:39 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char	*input;
	int		pid;
	t_mini	mini;

	(void) ac;
	(void) av;
	if (!msh_init(&mini, ev))
		return (1);
	input = NULL;
	while (!mini.exit)
	{
		input = readline("> minishell: $ ");
		if (!input)
			return (1);
		add_history(input);
		if (msh_parse(&mini, input))
		{
			pid = fork();
			if (!pid)
			{
				msh_exec(mini.cmd);
				msh_clean(&mini);
			}
			else if (pid > 0)
				wait(NULL);
		}
		free(input);
	}
	return (0);
}

int	msh_init(t_mini *mini, char **ev)
{
	if (!mini || !ev)
		return (0);
	mini->cmd = NULL;
	mini->env = init_env_array(ev);
	mini->exitcode = 0;
	mini->exit = 0;
	return (1);
}

int	msh_parse(t_mini *mini, const char *str)
{
	char	**split;

	if (!mini || !str)
		return (0);
	split = ft_split(str, '|');
	if (!split)
		return (0);
	mini->cmdc = ft_wc(str, "|");
	mini->cmd = ft_calloc(mini->cmdc, sizeof(t_cmd));
	if (!mini->cmd)
	{
		ft_free2d((void **) split);
		return (0);
	}
	msh_parse_commands(mini, split);
	ft_free2d((void **) split);
	return (1);
}

int	msh_isbuiltin(t_cmd *cmd)
{
	return (!ft_strncmp(*cmd->cmd, "echo", ft_strlen(*cmd->cmd))
			|| !ft_strncmp(*cmd->cmd, "cd", ft_strlen(*cmd->cmd))
			|| !ft_strncmp(*cmd->cmd, "pwd", ft_strlen(*cmd->cmd))
			|| !ft_strncmp(*cmd->cmd, "export", ft_strlen(*cmd->cmd))
			|| !ft_strncmp(*cmd->cmd, "unset", ft_strlen(*cmd->cmd))
			|| !ft_strncmp(*cmd->cmd, "env", ft_strlen(*cmd->cmd))
			|| !ft_strncmp(*cmd->cmd, "exit", ft_strlen(*cmd->cmd)));
}

int	msh_exec(t_cmd *cmd)
{
	size_t	i;

	if (cmd->mini->cmdc > 1)
	{
		i = -1;
		while (++i < cmd->mini->cmdc - 1)
			msh_exec_pipe(&cmd[i]);
		msh_exec_util(&cmd[i]);
		return (1);
	}
	else if (cmd->mini->cmdc == 1)
	{
		msh_exec_util(cmd);
		return (1);
	}	
	return (0);
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
		dup2(p_fd[1], cmd->fd1);
		close(p_fd[0]);
		msh_exec_util(cmd);
	}
	else
	{
		dup2(p_fd[0], cmd->fd0);
		close(p_fd[1]);
		waitpid(pid, NULL, 0);
	}
	return (1);
}

int	msh_exec_util(t_cmd *cmd)
{
	if (msh_isbuiltin(cmd))
	{
		return (msh_exec_builtin(cmd));
	}
	else
	{
		cmd->cmd[0] = msh_getutil(cmd->mini, cmd->cmd);
		if (execve(cmd->cmd[0], cmd->cmd, cmd->mini->env))
			exit(printf("minishell: %s\n", strerror(errno)));
		exit(0);
	}
}

int	msh_exec_builtin(t_cmd *cmd)
{
	return (printf("minishell: builtin %s\n", *cmd->cmd));
}

int	msh_clean(t_mini *mini)
{
	size_t	iter;

	if (!mini)
		return (0);
	iter = -1;
	while (++iter < (size_t) mini->cmdc)
		ft_free2d((void **) mini->cmd[iter].cmd);
	free(mini->cmd);
	mini->cmdc = 0;
	return (0);
}

int	msh_parse_commands(t_mini *mini, char **split)
{
	char	**split1;
	size_t	iter;

	if (!mini || !split)
		return (0);
	iter = 0;
	while (*split)
	{
		split1 = ft_split(*split, ' ');
		if (!split1)
			return (0);
		mini->cmd[iter].mini = mini;
		mini->cmd[iter].exit = 0;
		mini->cmd[iter].fd0 = 0;
		mini->cmd[iter].fd1 = 1;
		mini->cmd[iter].cmd = ft_strdup2d(split1, 0, ft_arrsiz2d((void **) split1));
		ft_free2d((void **) split1);
		iter++;
		split++;
	}
	return (1);
}

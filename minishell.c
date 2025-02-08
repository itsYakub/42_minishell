/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/08 08:48:51 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	main(int ac, char **av, char **ev)
{
	t_mini	mini;
	char	*input;

	(void) ac;
	(void) av;
	if (!msh_init(&mini, ev))
		return (1);
	input = NULL;
	while (1)
	{
		input = readline("> minishell: $ ");
		if (!input)
			return (printf("EOF reached!\n"));
		add_history(input);
		if (msh_parse(&mini, input))
		{
			msh_exec(mini.cmd);
			msh_clean(&mini);
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

int	msh_exec(t_cmd *cmd)
{
	size_t	i;

	if (cmd->mini->cmdc > 1)
	{
		i = -1;
		while (++i < cmd->mini->cmdc - 1)
			msh_exec_pipe(&cmd[i]);
		cmd[i].pid = fork();
		if (!cmd[i].pid)
			msh_exec_util(&cmd[i]);
		else if (cmd[i].pid > 0)
			wait(NULL);
		return (1);
	}
	else if (cmd->mini->cmdc == 1)
	{
		cmd->pid = fork();
		if (!cmd->pid)
			msh_exec_util(cmd);
		else if (cmd->pid > 0)
			wait(NULL);
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
		close(p_fd[0]);
		dup2(p_fd[1], cmd->fd1);
		msh_exec_util(cmd);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], cmd->fd0);
		waitpid(pid, NULL, 0);
	}
	return (1);
}

/*
 *	NOTE:	We can now check if cmd is a builtin or not with a simple 'if'
 *			The current code should be placed in one if block, and the builtins in another
 *			(BUILTINS doesn't require forking, remember!)
 * */
int	msh_exec_util(t_cmd *cmd)
{
	cmd->cmd[0] = msh_getutil(cmd->mini, cmd->cmd);
	if (execve(cmd->cmd[0], cmd->cmd, cmd->mini->env))
	{
		printf("minishell: %s\n", strerror(errno));
		exit(1);
	}
	exit(0);
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

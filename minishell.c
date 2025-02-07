/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/07 17:46:23 by lwillis          ###   ########.fr       */
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
	mini->cmd = ft_calloc(ft_wc(str, "|"), sizeof(t_cmd));
	mini->cmdc = ft_wc(str, "|");
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
	// start changes
	
	// This won't work with flags as is because my implementation splits the string later.
	// Easy enough to pass in the already split version.
	// But it works with ls | cat, or ls | cat | cat, for example.
	
	if (cmd->mini->cmdc > 1)
	{
		size_t i = 0;
		while (i < cmd->mini->cmdc - 1)
		{
			cmd_process(cmd[i].cmd[0], cmd->mini->env);
			i++;
		}
		do_cmd(cmd[i].cmd[0], cmd->mini->env);
		return (1);
	}

	// end changes
	
	else if (cmd->mini->cmdc == 1)
	{
		cmd->pid = fork();
		if (!cmd->pid)
		{
			msh_exec_util(cmd);
		}
		wait(NULL);
		return (1);
	}	
	return (0);
}

static int	__msh_close_pipe(int *pipefd, size_t c)
{
	while (--c)
		close(pipefd[c]);
	return (1);
}

int	msh_exec_pipe(t_cmd *cmd)
{
	int		*pipefd;
	size_t	iter;
	
	pipefd = malloc(cmd->mini->cmdc * 2 * sizeof(int));
	iter = -1;
	while (++iter < cmd->mini->cmdc)
		pipe(pipefd + iter * 2);
	iter = -1;
	while (++iter < cmd->mini->cmdc)
	{
		cmd->pid = fork();
		if (!cmd->pid)
		{
			if (iter != 0)
				dup2(pipefd[(iter - 1) * 2], cmd->fd0);
			if (iter != cmd->mini->cmdc)
				dup2(pipefd[iter * 2 + 1], cmd->fd1);
			__msh_close_pipe(pipefd, cmd->mini->cmdc * 2);
			msh_exec_util(cmd);
		}
	}
	__msh_close_pipe(pipefd, cmd->mini->cmdc * 2);
	free(pipefd);
	while (wait(NULL) > 0)
		;
	return (1);
}

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

/*
 *	TODO:	reimplement a pipeline behaviour
 *			it should handle n-number of pipes
 *			Examples:
 *			- ls -l | cat -e
 *			- ls -l | cat -e | grep "user" | wc -l
 *			etc. etc.
 * */

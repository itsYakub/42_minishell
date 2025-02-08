/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/08 09:47:30 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

static int	__msh_close_pipefd(int *fd, size_t c);

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
			msh_exec(&mini);
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
	mini->env = ev;
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

int	msh_exec(t_mini *mini)
{
	if (mini->cmdc == 1)
		return (msh_exec_single(mini));
	else if (mini->cmdc > 1)
		return (msh_exec_pipeline(mini));
	return (0);
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

int	msh_exec_single(t_mini *mini)
{
	mini->cmd->pid = fork();
	if (!mini->cmd->pid)
	{
		dup2(mini->cmd->fd0, 0);
		dup2(mini->cmd->fd1, 1);
		*mini->cmd->cmd = msh_getutil(mini, mini->cmd->cmd);
		if (execve(mini->cmd->cmd[0], mini->cmd->cmd, mini->env))
			return (printf("minishell: unknown command '%s'\n", *mini->cmd->cmd));
		if (mini->cmd->fd0 != 0)
		{
			close(mini->cmd->fd0);
			mini->cmd->fd0 = 0;
		}
		if (mini->cmd->fd1 != 1)
		{
			close(mini->cmd->fd1);
			mini->cmd->fd1 = 1;
		}
	}
	wait((int *) &mini->cmd->exit);
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
int	msh_exec_pipeline(t_mini *mini)
{
	(void) mini;
	return (0);
}

static int	__msh_close_pipefd(int *fd, size_t c)
{
	while (--c)
		close(fd[c]);
	return (1);
}

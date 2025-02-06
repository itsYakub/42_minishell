/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/06 15:23:01 by joleksia         ###   ########.fr       */
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
	mini->cmd = (t_cmd *) ft_calloc(ft_wc(str, "|"), sizeof(t_cmd *));
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
	if (!mini)
		return (0);
	return (1);
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
	return (0);
}

int	msh_parse_commands(t_mini *mini, char **split)
{
	char	**split1;

	if (!mini || !split)
		return (0);
	while (*split)
	{
		split1 = ft_split(*split, ' ');
		if (!split1)
			return (0);
		mini->cmd->mini = mini;
		mini->cmd->exit = 0;
		mini->cmd->fd0 = 0;
		mini->cmd->fd1 = 1;
		mini->cmd->cmd = ft_strdup2d(split1, 0, ft_arrsiz2d((void **) split1));
		ft_free2d((void **) split1);
		split++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-cmd0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:29:33 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/12 08:03:48 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*__msh_extract(t_cmd *cmd, t_token *t);
static t_token	*__msh_ext_red(t_cmd *cmd, t_token *t);

int	msh_cmd_creat(t_mini *mini)
{
	t_token	*t;
	size_t	iter0;

	mini->cmd = ft_calloc(msh_cmd_count(mini) + 1, sizeof(t_cmd));
	if (!mini->cmd)
		return (0);
	t = mini->lexer.tokens;
	iter0 = 0;
	while (t && t->type != T_NULL)
	{
		/* (joleksia) Temporary solution for input redirection */
		if (t->type == T_GREAT || t->type == T_APPEND)
			t = t->next;
		else if (t->type == T_LOWER)
			t = __msh_ext_red(&mini->cmd[iter0++], t);
		else if (t->type == T_PIPE)
			t = t->next;
		else if (t->type == T_SQUOT || t->type == T_DQUOT)
			t = t->next;
		else if (t->type == T_KEY)
			t = __msh_extract(&mini->cmd[iter0++], t);
	}
	iter0 = -1;
	while (++iter0 < (size_t) mini->cmdc)
		mini->cmd[iter0].mini = mini;
	return (1);	
}

int	msh_cmd_count(t_mini *mini)
{
	t_token	*t;
	int		res;

	t = mini->lexer.tokens;
	res = 1;
	while (t->type != T_NULL)
	{
		res += (t->type == 8) || (t->type == 4) || (t->type == 5);
		t = t->next;
	}
	mini->cmdc = res++;
	return (res);
}

int	msh_cmd_free(t_mini *mini)
{
	size_t	iter;

	iter = -1;
	while (++iter < (size_t) mini->cmdc)
		ft_free2d((void **) mini->cmd[iter].args);
	free(mini->cmd);
	mini->cmdc = 0;
	return (1);
}

static t_token	*__msh_extract(t_cmd *cmd, t_token *t)
{
	t_token	*t0;
	size_t	iter;

	t0 = t;
	iter = 0;
	while (t0->type == T_KEY || t0->type == T_SQUOT || t0->type == T_DQUOT)
	{
		if (t0->type == T_KEY)
			iter++;
		t0 = t0->next;
	}
	cmd->args = ft_calloc(iter + 1, sizeof(char *));
	if (!cmd)
		return (0);
	iter = -1;
	t0 = t;
	while (t0->type == T_KEY || t0->type == T_SQUOT || t0->type == T_DQUOT)
	{
		if (t0->type == T_KEY)
			cmd->args[++iter] = ft_strdup(t0->data);
		t0 = t0->next;
	}
	cmd->type = C_CMD;
	return (t0);
}

static t_token	*__msh_ext_red(t_cmd *cmd, t_token *t)
{
	t_token	*t0;

	t0 = t->next;
	cmd->args = ft_calloc(3, sizeof(char *));
	if (!cmd)
		return (0);
	cmd->args[0] = ft_strdup("cat");
	cmd->args[1] = ft_strdup(t0->data);
	if (!ft_strncmp("<", t->data, ft_strlen(t->data)))
		cmd->type = C_INPUT;
	return (t0->next);
}

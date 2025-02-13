/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-cmd0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:29:33 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/13 10:40:33 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*__msh_extract(t_cmd *cmd, t_token *t);
static t_token	*__msh_extract_redir(t_cmd *cmd, t_token *t);
static t_cmd	*__msh_cmd_init(t_mini *mini);

int	msh_cmd_creat(t_mini *mini)
{
	t_token	*t;
	size_t	iter0;

	mini->cmd = __msh_cmd_init(mini);
	if (!mini->cmd)
		return (0);
	t = mini->lexer.tokens;
	iter0 = 0;
	while (t && t->type != T_NULL)
	{
		if (t->type >= T_LOWER && t->type <= T_APPEND)
			t = __msh_extract_redir(&mini->cmd[iter0++], t);
		else if (t->type == T_SQUOT || t->type == T_DQUOT)
			t = t->next;
		else if (t->type == T_KEY)
			t = __msh_extract(&mini->cmd[iter0++], t);
		else if (t->type == T_PIPE)
			t = t->next;
	}
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
		res += (t->type == 8) || (t->type >= 2 && t->type <= 5);
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

/*
 *	TODO: Extract the redirections
 * */
static t_token	*__msh_extract_redir(t_cmd *cmd, t_token *t)
{
	cmd->args = ft_calloc(2, sizeof(char *));
	*cmd->args = ft_strdup(t->next->data);
	cmd->type = (t_cmd_type) t->type;
	return (t->next->next);
}

static t_cmd	*__msh_cmd_init(t_mini *mini)
{
	size_t	iter;
	t_cmd	*cmd;

	cmd = ft_calloc(msh_cmd_count(mini), sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	iter = -1;
	while (++iter < (size_t) mini->cmdc)
	{
		cmd[iter].mini = mini;
		cmd[iter].stdfd[0] = dup(STDIN_FILENO);
		cmd[iter].stdfd[1] = dup(STDOUT_FILENO);
		cmd[iter].rdrfd[0] = 0;
		cmd[iter].rdrfd[1] = 1;
	}
	return (cmd);
}

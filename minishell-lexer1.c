/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-lexer1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:26:12 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/12 14:54:47 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__msh_token_free(t_token *t);

void	*msh_token(void)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	t->data = NULL;
	t->next = NULL;
	t->type = T_NULL;
	return (t);
}

int	msh_lexer_free(t_lexer *l)
{
	__msh_token_free(l->tokens);
	free(l->tokens);
	l->tcount = 0;
	return (0);
}

int	msh_lexer_validate(t_lexer *l)
{
	t_token	*t;
	int		single_quote;
	int		double_quote;

	t = l->tokens;
	single_quote = 0;
	double_quote = 0;
	while (t->type != T_NULL)
	{
		if (t->type == T_SQUOT)
			single_quote = !single_quote;
		else if (t->type == T_DQUOT)
			double_quote = !double_quote;
		if ((t->type >= T_LOWER && t->type <= T_APPEND) || t->type == T_PIPE)
		{
			if (t->next->type != T_KEY)
				return (0);
		}
		t = t->next;
	}
	return (!single_quote && !double_quote);
}

static int	__msh_token_free(t_token *t)
{
	if (t->type != T_NULL)
	{
		free(t->data);
		__msh_token_free(t->next);
		free(t->next);
	}
	return (1);
}

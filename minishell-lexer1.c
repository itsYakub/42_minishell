/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-lexer1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:26:12 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/10 08:34:05 by joleksia         ###   ########.fr       */
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

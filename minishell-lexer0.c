/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-lexer0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:21:48 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/12 14:42:00 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_lexer(const char *s, t_lexer *l)
{
	t_token	*t;

	l->tokens = msh_token();
	t = l->tokens;
	while (*s)
	{
		while ((*s >= 9 && *s <= 13) || *s == 32)
			s++;
		if (*s == '|')
			s += msh_process_pipe(s, &t);
		else if (*s == '<')
			s += msh_process_lower(s, &t);
		else if (*s == '>')
			s += msh_process_great(s, &t);
		else if (*s == '\'' || *s == '\"')
			s += msh_process_quot(s, &t);
		else
			s += msh_process_key(s, &t);
	}
	return (1);
}

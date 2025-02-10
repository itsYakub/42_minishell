/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-lexer2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:27:33 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/10 14:33:15 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_lexer_expand(t_lexer *l)
{
	t_token	*t;
	char	*tmp;

	t = l->tokens;
	tmp = NULL;
	while (t->type != T_NULL)
	{
		if (t->type == T_KEY)
		{
			if (ft_strchr(t->data, '$'))
			{
				/* Extract the variable */	
			}
		}
	}
	return (1);
}

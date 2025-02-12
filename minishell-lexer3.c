/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-lexer3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:39:53 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/12 14:54:32 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_process_lower(const char *s, t_token **t)
{
	char	*start;
	char	*end;

	start = (char *) s;
	end = (char *) s;
	while (*end && *end == '<')
		end++;
	if (end - start == 1)
		(*t)->type = T_LOWER;
	else if (end - start == 2)
		(*t)->type = T_HEREDOC;
	(*t)->data = ft_substr(s, 0, end - start);
	(*t)->next = msh_token();
	(*t) = (*t)->next;
	return (end - start);
}

int	msh_process_great(const char *s, t_token **t)
{
	char	*start;
	char	*end;

	start = (char *) s;
	end = (char *) s;
	while (*end && *end == '>')
		end++;
	if (end - start == 1)
		(*t)->type = T_GREAT;
	else if (end - start == 2)
		(*t)->type = T_APPEND;
	(*t)->data = ft_substr(s, 0, end - start);
	(*t)->next = msh_token();
	(*t) = (*t)->next;
	return (end - start);
}

int	msh_process_key(const char *s, t_token **t)
{
	const char	*c
		= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
		"0123456789,./?;:[]{}\\//-_=+`~!@#$%^&*()";
	char		*start;
	char		*end;

	start = (char *) s;
	end = (char *) s;
	while (*end && (ft_strchr(c, *end)))
		end++;
	(*t)->type = T_KEY;
	(*t)->data = ft_substr(s, 0, end - start);
	(*t)->next = msh_token();
	(*t) = (*t)->next;
	return (end - start);
}

int	msh_process_quot(const char *s, t_token **t)
{
	if (*s == '\'')
		(*t)->type = T_SQUOT;
	else if (*s == '\"')
		(*t)->type = T_DQUOT;
	(*t)->data = ft_substr(s, 0, 1);
	(*t)->next = msh_token();
	(*t) = (*t)->next;
	return (1);
}

int	msh_process_pipe(const char *s, t_token **t)
{
	(*t)->type = T_PIPE;
	(*t)->data = ft_substr(s, 0, 1);
	(*t)->next = msh_token();
	(*t) = (*t)->next;
	return (1);
}

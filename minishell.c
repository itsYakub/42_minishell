/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/08 15:13:15 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__msh_print(t_lexer *l)
{
	t_token *t;

	for (t = l->tokens ; t->type != T_NULL; t = t->next)
	{
		printf("[ token : \"%s\" | ", t->data);
		if (t->type == T_KEY)
			printf("type : T_KEY ]\n");
		else if (t->type == T_DQUOT)
			printf("type : T_DQUOT ]\n");
		else if (t->type == T_SQUOT)
			printf("type : T_SQUOT ]\n");
		else if (t->type == T_GREAT)
			printf("type : T_GREAT ]\n");
		else if (t->type == T_HEREDOC)
			printf("type : T_HEREDOC ]\n");
		else if (t->type == T_LOWER)
			printf("type : T_LOWER ]\n");
		else if (t->type == T_APPEND)
			printf("type : T_APPEND ]\n");
		else if (t->type == T_PIPE)
			printf("type : T_PIPE ]\n");
	}
	return (1);
}

int	main(int ac, char **av, char **ev)
{
	t_lexer	lexer;
	char	*input;

	(void) ac;
	(void) av;
	(void) ev;
	input = NULL;
	lexer = (t_lexer) { 0 };
	while (1)
	{
		input = readline("> minishell: $ ");
		if (!input)
			return (1);
		add_history(input);
		msh_lexer(input, &lexer);
		__msh_print(&lexer);
		msh_token_free(lexer.tokens);
		free(lexer.tokens);
		free(input);
	}
	return (0);
}

static void	*__msh_token_init(void)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	t->data = NULL;
	t->next = NULL;
	t->type = T_NULL;
	return (t);
}

static int	__msh_process_white(const char *s)
{
	char	*s0;

	s0 =(char *) s;
	while ((*s0 >= 9 && *s0 <= 13) || *s0 == 32)
		s0++;	
	return (s0 - s);
}

static int	__msh_process_lower(const char *s, t_token **t)
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
	(*t)->next = __msh_token_init();
	(*t) = (*t)->next;
	return (end - start);
}

static int	__msh_process_great(const char *s, t_token **t)
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
	(*t)->next = __msh_token_init();
	(*t) = (*t)->next;
	return (end - start);
}

static int	__msh_process_multi(const char *s, t_token **t, int type, char *c)
{
	char	*start;
	char	*end;

	start = (char *) s;
	end = (char *) s;
	while (*end && (ft_strchr(c, *end)))
		end++;
	(*t)->type = type;
	(*t)->data = ft_substr(s, 0, end - start);
	(*t)->next = __msh_token_init();
	(*t) = (*t)->next;
	return (end - start);
}

static int	__msh_process_single(const char *s, t_token **t, int type)
{
	(*t)->type = type;
	(*t)->data = ft_substr(s, 0, 1);
	(*t)->next = __msh_token_init();
	(*t) = (*t)->next;
	return (1);
}

int	msh_lexer(const char *s, t_lexer *l)
{
	t_token	*t;

	l->tokens = __msh_token_init();
	t = l->tokens;
	while (*s)
	{
		if ((*s >= 9 && *s <= 13) || *s == 32)
			s += __msh_process_white(s);
		else if (*s == '|')
			s += __msh_process_single(s, &t, T_PIPE);
		else if (*s == '<')
			s += __msh_process_lower(s, &t);
		else if (*s == '>')
			s += __msh_process_great(s, &t);
		else if (*s == '\"')
			s += __msh_process_single(s, &t, T_DQUOT);
		else if (*s == '\'')
			s += __msh_process_single(s, &t, T_SQUOT);
		else
			s += __msh_process_multi(s, &t, T_KEY,
					"abcdefghijklmnopqrstuvwxyz"
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-_");
	}
	return (1);
}

int	msh_token_free(t_token *t)
{
	if (t->type != T_NULL)
	{
		free(t->data);
		msh_token_free(t->next);
		free(t->next);
	}
	return (1);
}

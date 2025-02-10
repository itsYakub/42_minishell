/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/10 08:35:36 by joleksia         ###   ########.fr       */
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
		msh_lexer_free(&lexer);
		free(input);
	}
	return (0);
}

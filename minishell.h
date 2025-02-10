/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:12:07 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/10 08:36:18 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*	SECTION:
 *		Headers	
 * */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_token	t_token;
typedef struct s_lexer	t_lexer;

typedef enum e_token_type
{
	T_KEY =	0,
	T_NULL,
	T_LOWER,
	T_HEREDOC,
	T_GREAT,
	T_APPEND,
	T_SQUOT,
	T_DQUOT,
	T_PIPE
}	t_token_type;

typedef struct s_token
{
	t_token	*next;
	char	*data;
	int		type;
}	t_token;

typedef struct s_lexer
{
	t_token	*tokens;
	size_t	tcount;
}	t_lexer;

/* ./minishell-lexer0.c ./minishell-lexer1.c*/

void	*msh_token(void);
int		msh_lexer(const char *s, t_lexer *l);
int		msh_lexer_free(t_lexer *l);

#endif

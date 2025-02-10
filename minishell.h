/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:12:07 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/10 11:01:59 by joleksia         ###   ########.fr       */
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

/*	SECTION:
 *		Typedefs
 * */

// linked list vars - might change
// typedef struct s_env
// {
// 	char			*var;
// 	struct s_env	*next;
// }	t_env;

// global var for signal received
typedef struct s_signal
{
	
}	t_signal;

typedef struct s_mini	t_mini;
typedef struct s_cmd	t_cmd;
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

typedef struct s_cmd
{
	char	**cmd;
	t_mini	*mini;
	char	exit;
	int		pid;
	int		fd0;
	int		fd1;
}	t_cmd;

typedef struct s_mini
{
	t_cmd	*cmd;
	size_t	cmdc;
	char	**env;
	char	exitcode;
	int		exit;
}	t_mini;

/*	SECTION:
 *		API
 * */

int	msh_init(t_mini *mini, char **ev);

int	msh_isbuiltin(t_cmd *cmd);

int	msh_exec(t_cmd *cmd);
int	msh_exec_pipe(t_cmd *cmd);
int	msh_exec_util(t_cmd *cmd);
int	msh_exec_builtin(t_cmd *cmd);

/* ./minishell-lexer0.c ./minishell-lexer1.c*/

void	*msh_token(void);
int		msh_lexer(const char *s, t_lexer *l);
int		msh_lexer_free(t_lexer *l);

// lw functions
// builtins
void	ms_cd(char *new_dir, char *env_vars[]);
void	ms_env(char *env_vars[]);
void	ms_echo(t_cmd cmd);
void	ms_exit(void);
void	ms_export(t_cmd cmd, char *env_vars[]);
void	ms_pwd(char *env_vars[]);
void	ms_unset(t_cmd cmd, char *env_vars[]);

// env_array
int		cmd_equals(const char *cmd, char *param);
char	**init_env_array(char *envp[]);
void	copy_env_array(char *old[], char **new[]);
int		count_array(char **array);
int		env_var_pos(char *var_name, char **env_var);
char	*env_var(char *var_name, char **env_vars);
int		empty_var(char *var_name, char **env_vars);

char	*msh_getutil(t_mini *mini, char **util);
char	*msh_getenv(t_mini *mini, const char *env);

#endif

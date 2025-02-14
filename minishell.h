/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:12:07 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/14 15:43:10 by lwillis          ###   ########.fr       */
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

// to make pipes a bit easier to understand
# define CURRENT_CMD 0
# define PREVIOUS_CMD 1
# define READ_END 0
# define WRITE_END 1

/*	SECTION:
 *		Typedefs
 * */

typedef int t_pipe[2];

typedef struct s_mini	t_mini;
typedef struct s_cmd	t_cmd;
typedef struct s_command	t_command;
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

typedef enum e_lexer_mode
{
	M_CMD,
	M_SQUOT,
	M_DQUOT
}	t_lexer_mode;

typedef enum e_cmd_type
{
	C_NULL = 0,
	C_CMD,
	C_INPUT,
	C_HEREDOC,
	C_OUTPUT,
	C_APPEND
}	t_cmd_type;

typedef struct s_token
{
	t_token	*next;
	char	*data;
	int		type;
}	t_token;

typedef struct s_lexer
{
	t_token	*tokens;
	t_mini	*mini;
	size_t	tcount;
}	t_lexer;

typedef struct s_mini
{
	t_lexer	lexer;
	t_cmd	*cmd;
	t_command	*commands;
	char	**env;
	int		cmdc;
	int		exitcode;
	int		exit;
	int		pid;
	int		current_cmd;
}	t_mini;

typedef struct s_cmd
{
	t_cmd_type	type;
	t_mini		*mini;
	char		**args;
	char		*fpath;
	int			stdfd[2];
	int			rdrfd[2];
	char		*infilename; // also used for heredoc delimiter
	char		*outfilename;
	int			inputtype; // 0 = file, 1 = heredoc, ignored if infilename is NULL
	int			outputtype; // 0 = trunc, 1 = append, ignored if outfilename is
}	t_cmd;

typedef struct s_command
{
	t_mini	*mini;
	char	*orig;
	char	**args;
	char	*infilename; // also used for heredoc delimiter
	char	*other_outfilenames;
	char	*outfilename;
	int		inputtype; // 0 = file, 1 = heredoc, ignored if infilename is NULL
	int		outputtype; // 0 = trunc, 1 = append, ignored if outfilename is
}	t_command;

/*	SECTION:
 *		API
 * */

int		msh_init(t_mini *mini, char **ev);
int		msh_parse(t_mini *mini, const char *s);
int		msh_clear(t_mini *mini);

/* ./minishell-exec0.c */

int		msh_exec(t_mini *mini);
int		msh_exec_pipe(t_cmd *cmd);
int		msh_exec_util(t_cmd *cmd);
int		msh_exec_builtin(t_cmd *cmd);
int		msh_isbuiltin(t_cmd *cmd);

/* ./minishell-lexer0.c ./minishell-lexer1.c ./minishell-lexer2.c */

void	*msh_token(void);
int		msh_lexer(const char *s, t_lexer *l);
int		msh_lexer_free(t_lexer *l);
int		msh_lexer_validate(t_lexer *l);
int		msh_lexer_expand(t_lexer *l);
int		msh_process_lower(const char *s, t_token **t);
int		msh_process_great(const char *s, t_token **t);
int		msh_process_key(const char *s, t_token **t);
int		msh_process_quot(const char *s, t_token **t);
int		msh_process_pipe(const char *s, t_token **t);

/* ./minishell-cmd0.c */
int		msh_cmd_creat(t_mini *mini);
int		msh_cmd_count(t_mini *mini);
int		msh_cmd_free(t_mini *mini);

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

// lw functions
// builtins
void	ms_cd(t_cmd *cmd);
void	ms_env(t_cmd *cmd);
void	ms_echo(t_cmd *cmd);
void	ms_exit(t_cmd *cmd);
void	ms_export(t_cmd *cmd);
void	ms_pwd(t_command *cmd);
void	ms_unset(t_cmd *cmd);

// env_array
char	*env_value_from_index(int pos, char **env_vars);
char	*env_value(char *var_name, t_mini *mini);
int		env_var_index(char *var_name, char **env_var);
char	*env_var(char *var_name, char **env_vars);
int		count_array(char **array);

// init
char	**init_env_array(char **envp);
void	copy_env_array(char **original, char ***copy);
void	free_stringlist(char **env_vars);

// lw_utils
char	*join_and_free(char *old, char *new);
char	*add_char_and_free(char *old, char new);

// cmd_parser
int		parse_and_execute(t_mini *mini, char *line);

// cmd_splitter
int		split_commands(t_mini *mini, char *line);

// cmd_expander
int		expand_commands(t_mini *mini);

// cmd_redirector
int		redirect_commands(t_mini *mini);

// cmd_checker
int		check_commands(t_mini *mini);

// cmd_executor
int		execute_commands(t_mini *mini);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:12:07 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/21 09:22:56 by lwillis          ###   ########.fr       */
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
# include <errno.h>
# include "../libft/libft.h"

// to make pipes a bit easier to understand
# define CURRENT_CMD 0
# define PREVIOUS_CMD 1
# define READ_END 0
# define WRITE_END 1
# define DEBUG 1

/*	SECTION:
 *		Typedefs
 * */

typedef enum e_parse_state
{
	EMPTY,
	QUOTE,
	TEXT
}							t_parse_state;

typedef int					t_pipe[2];

typedef struct s_mini		t_mini;
typedef struct s_command	t_command;

typedef struct s_mini
{
	t_command	*cmds;
	char		**env;
	int			cmdc;
	int			exitcode;
	int			current_cmd;
}	t_mini;

typedef struct s_command
{
	t_mini	*mini;
	char	*orig;
	char	**args;
	char	*infilename; // also used for heredoc delimiter
	char	*other_outnames;
	char	*outname;
	int		inputtype; // 0 = file, 1 = heredoc, ignored if no infilename
	int		outputtype; // 0 = trunc, 1 = append, ignored if no outfilename
}	t_command;

/*	SECTION:
 *		API
 * */

// builtins
void	ms_cd(t_command *cmd);
void	ms_env(t_command *cmd);
void	ms_echo(t_command *cmd);
void	ms_exit(t_command *cmd);
void	ms_export(t_command *cmd);
void	ms_pwd(t_command *cmd);
void	ms_unset(t_command *cmd);

// minishell
int		print_error(char *error_param);

// env_array
char	*env_value_from_index(int pos, char **env_vars);
char	*env_value(char *var_name, t_mini *mini, int in_quote);
int		env_var_index(char *var_name, char **env_var);
char	*env_var(char *var_name, char **env_vars);

// str_utils
char	*join_and_free(char *old, char *new);
char	*add_char_and_free(char *old, char new);
char	**sort_vars(t_command *cmd);
int		str_disallowed(char *str);
int		is_unprintable(char *str);

// cmd_parser
void	parse_and_execute(t_mini *mini, char *line);

// cmd_splitter
int		split_commands(t_mini *mini, char *line);

// cmd_expander
int		expand_commands(t_mini *mini);

// cmd_redirector
int		redirect_commands(t_mini *mini);

// cmd_checker
int		valid_commands(t_mini *mini);

// cmd_executor
int		execute_commands(t_mini *mini);

// arg_splitter
char	**split_args(char *s);

// cmd_piper
void	connect_pipes(t_mini *mini, t_pipe pipes[2]);
void	close_pipes(t_mini *mini, t_pipe pipes[2]);
void	swap_pipes(int **pipes);

// cmd_builtins
void	msh_exec_builtin(t_command *cmd);
int		msh_isbuiltin(t_command *cmd);

// msh_getutil
char	*msh_getutil(t_mini *mini, char **util);
int		handle_other_filenames(t_command *cmd);

// env_utils
int		count_array(char **array);
void	copy_env_array(char **original, char ***copy);
char	**init_env_array(char **envp);

// signals
void	enable_ctrl_c(int sig);
void	disable_ctrl_c(int sig);

// cmd_redir_setup
int		set_output(t_command *cmd, int *start, int in_quote, int in_apo);
int		set_input(t_command *cmd, int *start, int in_quote, int in_apo);

// cmd_printer
void	print_commands(t_mini *mini);

#endif

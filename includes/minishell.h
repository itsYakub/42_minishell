/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:12:07 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/17 14:36:26 by lwillis          ###   ########.fr       */
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
# include "../libft/libft.h"

// to make pipes a bit easier to understand
# define CURRENT_CMD 0
# define PREVIOUS_CMD 1
# define READ_END 0
# define WRITE_END 1

/*	SECTION:
 *		Typedefs
 * */

typedef enum e_parse_state
{	
	EMPTY,
	QUOTE,
	TEXT
}	t_parse_state;

typedef int t_pipe[2];

typedef struct s_mini	t_mini;
typedef struct s_command	t_command;

typedef struct s_mini
{
	t_command	*commands;
	char	**env;
	int		cmdc;
	int		exitcode;
	int		pid;
	int		current_cmd;
}	t_mini;

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

// env_array
int		cmd_equals(const char *cmd, char *param);
char	**init_env_array(char *envp[]);
void	copy_env_array(char *old[], char **new[]);
int		count_array(char **array);
int		env_var_pos(char *var_name, char **env_var);
char	*env_var(char *var_name, char **env_vars);
int		empty_var(char *var_name, char **env_vars);

// builtins
void	ms_cd(t_command *cmd);
void	ms_env(t_command *cmd);
void	ms_echo(t_command *cmd);
void	ms_exit(t_command *cmd);
void	ms_export(t_command *cmd);
void	ms_pwd(t_command *cmd);
void	ms_unset(t_command *cmd);

// env_array
char	*env_value_from_index(int pos, char **env_vars);
char	*env_value(char *var_name, t_mini *mini, int in_quote);
int		env_var_index(char *var_name, char **env_var);
char	*env_var(char *var_name, char **env_vars);
int		count_array(char **array);

// utils
char	*join_and_free(char *old, char *new);
char	*add_char_and_free(char *old, char new);
void	free_stringlist(char **list);
void	copy_env_array(char **original, char ***copy);
char	**init_env_array(char **envp);

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

// arg_splitter
char	**split_args(char *s);
char	**lw_split(char const *s, char c);

#endif

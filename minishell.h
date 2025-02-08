/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:12:07 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/08 15:27:57 by lwillis          ###   ########.fr       */
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

// global var for signal received
typedef struct s_signal
{
	
}	t_signal;

typedef struct s_mini	t_mini;
typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char	**cmd;
	t_mini	*mini;
	char	exit;
	int		pid;
	int		fd0;
	int		fd1;
	int	ppid;
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

int		msh_init(t_mini *mini, char **ev);
int		msh_parse(t_mini *mini, const char *str);
int		msh_exec(t_cmd *cmd);
int		msh_clean(t_mini *mini);
int		msh_exec_pipe(t_cmd *cmd);
int		msh_exec_util(t_cmd *cmd);
int		msh_exec_builtin(t_cmd *cmd);

int		msh_parse_commands(t_mini *mini, char **split);
int		msh_parse_cmd(t_cmd *cmd, char **split);

int		msh_exec_single(t_mini *mini);
int		msh_exec_pipeline(t_mini *mini);

char	*msh_getutil(t_mini *mini, char **util);
char	*msh_getenv(t_mini *mini, const char *env);

// lw functions
// builtins
void	ms_cd(t_cmd *cmd);
void	ms_env(t_cmd *cmd);
void	ms_echo(t_cmd *cmd);
void	ms_exit(t_cmd *cmd);
void	ms_export(t_cmd *cmd);
void	ms_pwd(t_cmd *cmd);
void	ms_unset(t_cmd *cmd);

// lw
int		cmd_equals(const char *cmd, char *param);

// env_array
char	*env_value_from_index(int pos, char **env_vars);
char	*env_value(char *var_name, char **env_vars);
int		env_var_index(char *var_name, char **env_var);
char	*env_var(char *var_name, char **env_vars);
int		count_array(char **array);

// init
char	**init_env_array(char **envp);
void	copy_env_array(char **original, char ***copy);
void	free_stringlist(char **env_vars);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:12:07 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/07 10:42:29 by lwillis          ###   ########.fr       */
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
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

/*	SECTION:
 *		Typedefs
 * */

// linked list vars - might change
typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

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
}	t_cmd;

typedef struct s_mini
{
	t_cmd	*cmd;
	size_t	cmdc;
	char	**env;
	char	exit;
}	t_mini;

/*	SECTION:
 *		API
 * */

int	msh_init(t_mini *mini, char **ev);
int	msh_parse(t_mini *mini, const char *str);
int	msh_exec(t_mini *mini);
int	msh_clean(t_mini *mini);

int	msh_parse_commands(t_mini *mini, char **split);
int	msh_parse_cmd(t_cmd *cmd, char **split);

// lw functions
t_env	*env_var_node(char *str, t_env *env_vars);
char	*env_var(char *str, t_env *env_vars);
void	init_env_vars(t_env **head, char *envp[]);
void	ms_exit(void);
void	ms_pwd(t_env *env_vars);
void	ms_cd(char *new_dir, t_env *env_vars);
void	ms_env(t_env *env_vars);
void	ms_echo(t_cmd cmd);
int		cmd_equals(const char *cmd, char *param);
void	ms_export(t_cmd cmd, t_env *env_vars);
void	ms_unset(t_cmd cmd, t_env *env_vars);
char	**init_env_array(char *envp[]);
void	copy_env_array(char *old[], char **new[]);
int		count_array(char **array);

#endif

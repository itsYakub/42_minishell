/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lw.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:35:52 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 10:44:27 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include "../minishell.h"
# include <string.h>
# include <dirent.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>

t_signal	g_signal;

// ctrl + c
// copied, not tested
void	sig_int(int code)
{
	(void)code;
    write(2, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

// ctr + "\"
void	sig_quit(int code)
{
	(void)code;
	ms_exit();
}

// copied, not tested
void	init_g_signal(void)
{
	// g_signal.sigint = 0;
	// g_signal.sigquit = 0;
	// g_signal.pid = 0;
	// g_signal.exit_status = 0;
}

int	cmd_equals(const char *cmd, char *param)
{
	int	result;
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	result = ft_strncmp(cmd, param, cmd_len);
	return (!result && ft_strlen(param) == cmd_len);
}

int	get_builtin(t_cmd cmd, t_env *env_vars)
{
	// split string, check arguments
	if (cmd_equals("pwd", cmd.cmd[0]))
	{
		ms_pwd(env_vars);
	}
	if (cmd_equals("cd", cmd.cmd[0]))
	{
		// no args = got home
		ms_cd("..", env_vars);
	}
	if (cmd_equals("exit", cmd.cmd[0]))
	{
		ms_exit();
	}
	if (cmd_equals("env", cmd.cmd[0]))
	{
		ms_env(env_vars);
	}
	if (cmd_equals("export", cmd.cmd[0]))
	{
		ms_export(cmd, env_vars);
	}
	if (cmd_equals("echo", cmd.cmd[0]))
	{
		ms_echo(cmd);
	}
	if (cmd_equals("unset", cmd.cmd[0]))
	{
		ms_unset(cmd, env_vars);
	}
	return (0);
}

void	lw(int argc, char *argv[], char *envp[])
{	
	t_env	*env_vars;
	
	env_vars = NULL;
	init_env_vars(&env_vars, envp);
	char	*line_read = "";
	
	(void)argc;
	(void)argv;
	
	init_g_signal();
	
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);

	while(1)
	{
		line_read = readline("Prompt > ");
		add_history(line_read);
		t_cmd cmd;
		cmd.cmd = ft_split(line_read, ' ');
		get_builtin(cmd, env_vars);
	}

	// free env_vars
}

int	main(int argc, char *argv[], char *envp[])
{	
	init_env_array(envp);
	lw(argc, argv, envp);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lw.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:35:52 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 16:42:10 by lwillis          ###   ########.fr       */
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

int	get_builtin(t_mini *mini)
{
	// split string, check arguments
	if (cmd_equals("pwd", mini->cmd->cmd[0]))
	{
		ms_pwd(mini);
	}
	if (cmd_equals("cd", mini->cmd->cmd[0]))
	{
		ms_cd(mini);
	}
	if (cmd_equals("exit", mini->cmd->cmd[0]))
	{
		ms_exit();
	}
	if (cmd_equals("env", mini->cmd->cmd[0]))
	{
	
		ms_env(mini);
	}
	if (cmd_equals("export", mini->cmd->cmd[0]))
	{
		ms_export(mini);
	}
	if (cmd_equals("echo", mini->cmd->cmd[0]))
	{
		ms_echo(mini);
	}
	if (cmd_equals("unset", mini->cmd->cmd[0]))
	{
		ms_unset(mini);
	}
	return (0);
}

void	lw(t_mini *mini)
{	
	char	*line_read = "";
	
	init_g_signal();
	
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);

	while(1)
	{
		line_read = readline("Prompt > ");
		add_history(line_read);
		mini->cmd->fd0 = 0;
		mini->cmd->fd1 = 1;
		mini->cmd->cmd = ft_split(line_read, ' ');
		get_builtin(mini);
	}	
}

int	main(int argc, char *argv[], char *envp[])
{	
	t_mini	mini;

	(void)argc;
	(void)argv;

	mini.env = init_env_array(envp);
	mini.cmd = malloc(sizeof(t_cmd));
	if (!mini.env)
	{
		printf("Couldn't create env vars :(");
		return (1);
	}
	lw(&mini);
	free_stringlist(mini.env);
	return 0;
}

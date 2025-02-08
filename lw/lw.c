/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lw.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:35:52 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/08 13:48:17 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include "../minishell.h"
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <readline/readline.h>

t_signal	g_signal;

// ctrl + c
// copied, not tested
void	sig_int(int code)
{
	(void)code;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// ctr + "\"
void	sig_quit(int code)
{
	(void)code;
}

// copied, not tested
// void	init_g_signal(void)
// {
// 	// g_signal.sigint = 0;
// 	// g_signal.sigquit = 0;
// 	// g_signal.pid = 0;
// 	// g_signal.exit_status = 0;
// }

int	cmd_equals(const char *cmd, char *param)
{
	int	result;
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	result = ft_strncmp(cmd, param, cmd_len);
	return (!result && ft_strlen(param) == cmd_len);
}

int	get_builtin(t_cmd *cmd)
{
	if (cmd_equals("pwd", cmd->cmd[0]))
		ms_pwd(cmd);
	if (cmd_equals("cd", cmd->cmd[0]))
		ms_cd(cmd);
	if (cmd_equals("exit", cmd->cmd[0]))
		ms_exit(cmd);
	if (cmd_equals("env", cmd->cmd[0]))
		ms_env(cmd);
	if (cmd_equals("export", cmd->cmd[0]))
		ms_export(cmd);
	if (cmd_equals("echo", cmd->cmd[0]))
		ms_echo(cmd);
	if (cmd_equals("unset", cmd->cmd[0]))
		ms_unset(cmd);
	return (0);
}

void	lw(t_mini *mini)
{
	char	*line_read;

	//init_g_signal();	
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	line_read = "";
	while (1)
	{
		mini->cmd = malloc(sizeof(t_cmd));
		line_read = readline("Prompt > ");
		add_history(line_read);
		mini->cmd->fd0 = 0;
		mini->cmd->fd1 = 1;
		mini->cmd->cmd = ft_split(line_read, ' ');
		mini->cmd->mini = mini;
		get_builtin(mini->cmd);
		free_stringlist(mini->cmd->cmd);
		free(mini->cmd);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	mini.env = init_env_array(envp);
	if (!mini.env)
	{
		printf("Couldn't create env vars :(");
		return (1);
	}
	lw(&mini);
	return (0);
}

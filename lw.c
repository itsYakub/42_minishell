/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lw.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:35:52 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/06 16:36:48 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include "minishell.h"
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

int	get_builtin(char *str, t_env *env_vars)
{
	// split string, check arguments
	if (0 == ft_strncmp(str, "pwd", 3) && 3 == ft_strlen(str))
	{
		ms_pwd(env_vars);
	}
	if (0 == ft_strncmp(str, "cd", 2))
	{
		// no args = got home
		ms_cd("..", env_vars);
	}
	if (0 == ft_strncmp(str, "exit", 4) && 4 == ft_strlen(str))
	{
		ms_exit();
	}
	if (0 == ft_strncmp(str, "env", 3) && 3 == ft_strlen(str))
	{
		ms_env(env_vars);
	}
	if (0 == ft_strncmp(str, "export", 6))
	{
		// no args same as env?
		//ms_env(envp);
		//add_env_var("abc", "def", envp);
		// export key=value
	}
	if (0 == ft_strncmp(str, "echo", 4))
	{
		ms_echo(str);
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
		get_builtin(line_read, env_vars);
	}

	// free env_vars
}

int	main(int argc, char *argv[], char *envp[])
{	
	lw(argc, argv, envp);
	return 0;
}

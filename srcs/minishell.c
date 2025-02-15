/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/15 16:53:49 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigexit_handler(int sig)
{
	(void)sig;
	exit(0);
}

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
	The main loop, in its own thread
*/
static void	loop(t_mini *mini)
{	
	char	*input;
	
	while (!mini->exit)
	{
		input = readline("\033[0;34m\033[1m> minishell: $ \033[0m");
		if (!input)
		{
			// cleanup
			exit(0);
		}		
		add_history(input);
		parse_and_execute(mini, input);				
			// cleanup mini
		free(input);
	}
}

int	main(int ac, char **av, char **ev)
{
	int		pid;
	t_mini	mini;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGUSR1, sigexit_handler);
	signal(SIGQUIT, SIG_IGN);
	mini.cmdc = 0;
	mini.env = init_env_array(ev);
	mini.exit = 0;
	mini.exitcode = 0;
	pid = fork();
	if (0 == pid)
		loop(&mini);
	else
		waitpid(pid, NULL, 0);
	return (0);
}

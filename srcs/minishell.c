/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/19 14:12:42 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Prints an error found during execution
*/
int	print_error(char *error_param)
{
	ft_putstr_fd("minishell: ", 2);
	if (error_param)
	{
		ft_putstr_fd(error_param, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

/*
	Handles the ctrl+c combination
*/
void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
	Frees up memory after every main process command
*/
static void	cleanup(t_mini *mini)
{
	int	i;

	i = -1;
	while (++i < mini->cmdc)
	{
		free_stringlist(mini->commands[i].args);
		free(mini->commands[i].orig);
		free(mini->commands[i].infilename);
		free(mini->commands[i].outfilename);
		free(mini->commands[i].other_outfilenames);
	}
	free(mini->commands);
}

/*
	The main exec loop
*/
static void	loop(t_mini *mini)
{
	char	*input;

	while (1)
	{
		input = readline("\033[0;34m\033[1m> minishell: $ \033[0m");
		if (!input)
		{
			free_stringlist(mini->env);
			exit(0);
		}
		add_history(input);
		parse_and_execute(mini, input);
		cleanup(mini);
		free(input);
	}
}

/*
	Here we go!
*/
int	main(int ac, char **av, char **ev)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	mini.cmdc = 0;
	mini.exitcode = 0;
	mini.env = init_env_array(ev);
	loop(&mini);
	return (0);
}

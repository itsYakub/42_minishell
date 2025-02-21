/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/21 10:19:45 by lwillis          ###   ########.fr       */
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
	Frees up memory after every main process command
*/
static void	cleanup(t_mini *mini)
{
	int	i;

	i = -1;
	while (++i < mini->cmdc)
	{
		if (mini->cmds[i].args)
			ft_free2d((void **)mini->cmds[i].args);
		free(mini->cmds[i].orig);
		free(mini->cmds[i].infilename);
		free(mini->cmds[i].outname);
		free(mini->cmds[i].other_outnames);
	}
	free(mini->cmds);
}

/*
	The main exec loop
*/
static void	loop(t_mini *mini)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, enable_ctrl_c);
		input = readline("\033[0;36m\033[1m> minishell: $ \033[0m");
		signal(SIGINT, disable_ctrl_c);
		if (!input)
		{
			ft_free2d((void **)mini->env);
			exit(0);
		}
		if (is_unprintable(input))
			continue ;
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
	signal(SIGQUIT, SIG_IGN);
	mini.cmdc = 0;
	mini.exitcode = 0;
	mini.env = init_env_array(ev);
	loop(&mini);
	return (0);
}

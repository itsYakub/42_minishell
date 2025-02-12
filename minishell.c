/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/12 08:12:36 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int ac, char **av, char **ev)
{
	char	*input;
	t_mini	mini;

	(void) ac;
	(void) av;	
	if (!msh_init(&mini, ev))
		return (1);
	input = NULL;
	while (!mini.exit)
	{		
		input = readline("> minishell: $ ");
		if (input && ft_strlen(input))
		{
			add_history(input);
			if (msh_parse(&mini, input))
			{
				if (!msh_exec(&mini))
					printf("minishell: %s\n", strerror(errno));
				msh_clear(&mini);
			}
			free(input);
		}
	}
	return (0);
}

int	msh_init(t_mini *mini, char **ev)
{
	signal(SIGINT, sigint_handler);
	signal(SIGUSR1, sigexit_handler);
	signal(SIGQUIT, SIG_IGN);
	mini->cmd = NULL;
	mini->cmdc = 0;
	mini->env = init_env_array(ev);
	mini->exit = 0;
	mini->exitcode = 0;
	mini->lexer = (t_lexer) { 0 };
	mini->lexer.mini = mini;
	return (1);
}

int	msh_parse(t_mini *mini, const char *s)
{
	msh_lexer(s, &mini->lexer);
	if (!msh_lexer_validate(&mini->lexer))
		return (!printf("minishell: lexical error\n"));
	if (!msh_lexer_expand(&mini->lexer))
		return (!printf("minishell: parsing variables error\n"));
	if (!msh_cmd_creat(mini))
		return (!printf("minishell: command error\n"));
	return (1);
}

int	msh_clear(t_mini *mini)
{
	msh_lexer_free(&mini->lexer);
	msh_cmd_free(mini);
	return (1);
}

int	cmd_equals(const char *cmd, char *param)
{
	int	result;
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	result = ft_strncmp(cmd, param, cmd_len);
	return (!result && ft_strlen(param) == cmd_len);
}

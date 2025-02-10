/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/10 14:24:55 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
/*
			pid = fork();
			if (!pid)
			{
				msh_exec(mini.cmd);
				msh_clean(&mini);
			}
			else if (pid > 0)
				wait(NULL);
*/
		}
	}
	return (0);
}

int	msh_init(t_mini *mini, char **ev)
{
	if (!mini || !ev)
		return (0);
	mini->cmd = NULL;
	mini->cmdc = 0;
	mini->env = init_env_array(ev);
	mini->exit = 0;
	mini->exitcode = 0;
	mini->lexer = (t_lexer) { 0 };
	return (1);
}

int	msh_parse(t_mini *mini, const char *s)
{
	msh_lexer(s, &mini->lexer);
	if (!msh_lexer_validate(&mini->lexer))
	{
		printf("minishell: lexical error\n");
		return (0);
	}
	msh_expand(&mini->lexer);
	return (1);
}

int	msh_clear(t_mini *mini)
{
	msh_lexer_free(&mini->lexer);	
	return (1);
}

int	msh_exec(t_mini *mini)
{
	(void) mini;
	return (1);
}

int	msh_isbuiltin(t_cmd *cmd)
{
	(void) cmd;
	return (0);
}

int	msh_exec_pipe(t_cmd *cmd)
{
	int	pid;
	int	p_fd[2];

	if (-1 == pipe(p_fd))
		return (printf("minishell: %s\n", strerror(errno)));
	pid = fork();
	if (-1 == pid)
		return (printf("minishell: %s\n", strerror(errno)));
	if (0 == pid)
	{
		dup2(p_fd[1], cmd->rdrfd[1]);
		close(p_fd[0]);
		msh_exec_util(cmd);
	}
	else
	{
		dup2(p_fd[0], cmd->rdrfd[0]);
		close(p_fd[1]);
		waitpid(pid, NULL, 0);
	}
	return (1);
}

int	msh_exec_util(t_cmd *cmd)
{
	if (msh_isbuiltin(cmd))
	{
		return (msh_exec_builtin(cmd));
	}
	else
	{
		if (execve(cmd->args[0], cmd->args, cmd->mini->env))
			exit(printf("minishell: %s\n", strerror(errno)));
		exit(0);
	}
}

int	msh_exec_builtin(t_cmd *cmd)
{
	return (printf("minishell: builtin %s\n", *cmd->args));
}

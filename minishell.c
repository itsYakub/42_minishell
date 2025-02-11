/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:57:34 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/11 11:46:38 by lwillis          ###   ########.fr       */
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
	signal(SIGINT, sigint_handler);
	signal(SIGUSR1, sigexit_handler);
	
	// So you can use ctrl-d
	//signal(SIGQUIT, SIG_IGN);
	
	if (!msh_init(&mini, ev))
		return (1);

	input = NULL;
	while (!mini.exit)
	{		
		input = readline("> minishell: $ ");
		// So you can use ctrl-d
		if (!input)
			exit(0);
			
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
	if (!msh_lexer_expand(&mini->lexer, mini->env))
	{
		printf("minishell: parsing variables error\n");
		return (0);
	}
	msh_cmd_count(mini);
	msh_cmd_creat(mini);	
	return (1);
}

int	msh_clear(t_mini *mini)
{
	msh_lexer_free(&mini->lexer);
	msh_cmd_free(mini);
	return (1);
}

int	msh_exec(t_mini *mini)
{
	printf("=====\n");
	printf("Lexer:\n");
	printf("=====\n");
	for (t_token *t = mini->lexer.tokens; t->type != T_NULL; t = t->next)
		printf("%s\n", t->data);
	printf("=====\n");
	printf("Commands:\n");
	printf("=====\n");
	for (int i = 0; mini->cmd[i].type != C_NULL; i++)
	{
		for (int j = 0; mini->cmd[i].args[j]; j++)
			printf("%s ", mini->cmd[i].args[j]);
		printf("(Type: %i)\n", mini->cmd[i].type);
	}
	printf("=====\n");
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

int	cmd_equals(const char *cmd, char *param)
{
	int	result;
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	result = ft_strncmp(cmd, param, cmd_len);
	return (!result && ft_strlen(param) == cmd_len);
}

static int	get_builtin(t_cmd *cmd)
{
	if (cmd_equals("pwd", cmd->args[0]))
		ms_pwd(cmd);
	if (cmd_equals("cd", cmd->args[0]))
		ms_cd(cmd);
	if (cmd_equals("exit", cmd->args[0]))
		ms_exit(cmd);
	if (cmd_equals("env", cmd->args[0]))
		ms_env(cmd);
	if (cmd_equals("export", cmd->args[0]))
		ms_export(cmd);
	if (cmd_equals("echo", cmd->args[0]))
		ms_echo(cmd);
	if (cmd_equals("unset", cmd->args[0]))
		ms_unset(cmd);
	return (0);
}


int	msh_exec_builtin(t_cmd *cmd)
{
	return (get_builtin(cmd));
}

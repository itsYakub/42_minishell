/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:38:58 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/19 11:04:23 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Prepares the command to receive input from another fd, including heredoc
*/
static int	handle_cmd_input(t_command *cmd)
{
	int		input_fd;
	char	*line;

	if (1 == cmd->inputtype)
	{
		input_fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		while (1)
		{
			line = readline("> ");
			if (0 == ft_strcmp(cmd->infilename, line))
				break ;
			write(input_fd, line, ft_strlen(line));
			write(input_fd, "\n", 1);
		}
		close(input_fd);
		cmd->infilename = ".heredoc";
	}
	input_fd = open(cmd->infilename, O_RDONLY, 0644);
	if (input_fd < 0)
		return (0);
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	return (1);
}

/*
	Prepares the command to output to another fd, both trunc and append
*/
static int	handle_cmd_output(t_command *cmd)
{
	char	**split;
	int		i;
	int		output_fd;

	if (cmd->other_outfilenames)
	{
		split = ft_split(cmd->other_outfilenames, '\n');
		i = -1;
		while (split[++i])
		{
			output_fd = open(split[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(output_fd);
		}
		free_stringlist(split);
	}
	if (0 == cmd->outputtype)
		output_fd = open(cmd->outfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		output_fd = open(cmd->outfilename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	return (1);
}

static int	execute_child(t_command *cmd, t_pipe pipes[2])
{
	if (cmd->infilename)
	{
		if (!handle_cmd_input(cmd))
			exit(127);
	}
	connect_pipes(cmd->mini, pipes);
	if (cmd->outfilename)
	{
		if (!handle_cmd_output(cmd))
			exit(127);
	}
	if (msh_isbuiltin(cmd))
	{
		msh_exec_builtin(cmd);
		exit(127);
	}
	cmd->args[0] = msh_getutil(cmd->mini, cmd->args);
	if (execve(cmd->args[0], cmd->args, cmd->mini->env) < 0)
		exit(127);
	exit(0);
}

/*
	The main function the sets ups and runs the command
*/
static int	execute_cmd(t_command *cmd)
{
	static t_pipe	pipes[2];
	int				pid;

	pipe(pipes[CURRENT_CMD]);
	pid = fork();
	if (0 == pid)
		execute_child(cmd, pipes);
	else
		waitpid(pid, &cmd->mini->exitcode, 0);
	close_pipes(cmd->mini, pipes);
	swap_pipes((int **)pipes);
	return (1);
}

/*
	Loops through the commands and frees resources after each one
*/
int	execute_commands(t_mini *mini)
{
	int	i;

	if (1 == mini->cmdc && msh_isbuiltin(&mini->commands[0]))
	{
		msh_exec_builtin(&mini->commands[0]);
		return (1);
	}
	i = -1;
	while (++i < mini->cmdc)
	{
		mini->current_cmd = i;
		execute_cmd(&mini->commands[i]);
	}
	return (1);
}

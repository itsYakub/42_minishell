/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:38:58 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/21 14:50:21 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Prepares the command to receive input from another fd, including heredoc
*/
static int	handle_cmd_input(t_command *cmd)
{
	int		input_fd;

	if (1 == cmd->inputtype)
		heredoc_loop(cmd);
	input_fd = open(cmd->infilename, O_RDONLY, 0644);
	if (input_fd < 0)
		return (print_error(cmd->infilename));
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	return (1);
}

/*
	Prepares the command to output to another fd, both trunc and append
*/
static int	handle_cmd_output(t_command *cmd)
{
	int	output_fd;

	if (!handle_other_filenames(cmd))
		return (0);
	if (0 == cmd->outputtype)
		output_fd = open(cmd->outname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		output_fd = open(cmd->outname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (output_fd < 0)
		return (print_error(cmd->outname));
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	return (1);
}

/*
	Runs a command in a child process
*/
static int	execute_child(t_command *cmd, t_pipe pipes[2])
{
	if (cmd->infilename)
		if (!handle_cmd_input(cmd))
			exit(127);
	connect_pipes(cmd->mini, pipes);
	if (cmd->outname)
		if (!handle_cmd_output(cmd))
			exit(127);
	if (msh_isbuiltin(cmd))
	{
		msh_exec_builtin(cmd);
		exit(127);
	}
	cmd->args[0] = msh_getutil(cmd->mini, cmd->args);
	if (access(cmd->args[0], F_OK | X_OK))
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd("': command not found\n", 2);
		exit(127);
	}
	if (execve(cmd->args[0], cmd->args, cmd->mini->env) < 0)
		exit(127);
	exit(0);
}

/*
	The main function the sets ups and runs the command
*/
static int	execute_cmd(t_command *cmd, int current_cmd)
{
	static t_pipe	pipes[2];
	int				pid;

	cmd->mini->current_cmd = current_cmd;
	pipe(pipes[CURRENT_CMD]);
	pid = fork();
	if (0 == pid)
		execute_child(cmd, pipes);
	else
		waitpid(pid, &cmd->mini->exitcode, 0);
	if (cmd->mini->exitcode != 0)
		cmd->mini->exitcode = 1;
	else
		cmd->mini->exitcode = 0;
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
	int	in;
	int	out;

	if (1 == mini->cmdc && msh_isbuiltin(&mini->cmds[0]))
	{
		in = dup(0);
		out = dup(1);
		if (mini->cmds[0].infilename)
			if (!handle_cmd_input(&mini->cmds[0]))
				return (0);
		if (mini->cmds[0].outname)
			if (!handle_cmd_output(&mini->cmds[0]))
				return (0);
		msh_exec_builtin(&mini->cmds[0]);
		dup2(in, 0);
		dup2(out, 1);
		return (1);
	}
	i = -1;
	while (++i < mini->cmdc)
		execute_cmd(&mini->cmds[i], i);
	return (1);
}

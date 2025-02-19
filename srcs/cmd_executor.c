/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:38:58 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/19 09:53:01 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Prepares the command to receive input from another fd, including heredoc
*/
static void	handle_cmd_input(t_command *cmd)
{
	int		input_fd;
	char	*line;

	if (1 == cmd->inputtype)
	{
		// heredoc creates a temp file, loop appends to it, then continues as normal
		input_fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		while (1)
		{
			line = readline("> ");
			// infilename does double-duty as the delimiter. We can change this if it's confusing/bad practice
			if (0 == ft_strcmp(cmd->infilename, line))
				break;
			write(input_fd, line, ft_strlen(line));
			write(input_fd, "\n", 1);
		}
		close(input_fd);
		// if infilename is the delimiter, we need to set it back here
		cmd->infilename = ".heredoc";
	}
	input_fd = open(cmd->infilename, O_RDONLY, 0644); // error check		
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
}

/*
	Prepares the command to output to another fd, both trunc and append
*/
static void	handle_cmd_output(t_command *cmd)
{
	int	output_fd;

	if (cmd->other_outfilenames)
	{
		char **split = ft_split(cmd->other_outfilenames, '\n');
		int	i = -1;
		while (split[++i])
		{
			output_fd = open(split[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(output_fd);
		}
		free_stringlist(split);
	}
	if (0 == cmd->outputtype)
		output_fd = open(cmd->outfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644); // error check
	else
		output_fd = open(cmd->outfilename, O_WRONLY | O_CREAT | O_APPEND, 0644); // error check
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
}

/*
	The main function the sets ups and runs the command
*/
static void execute_cmd(t_command *cmd)
{
	static t_pipe 	pipes[2];
	int				pid;

	pipe(pipes[CURRENT_CMD]); // ec
	pid = fork(); // ec	
	if (0 == pid)
	{
		if (cmd->infilename)
			handle_cmd_input(cmd);
		connect_pipes(cmd->mini, pipes);
		if (cmd->outfilename)
			handle_cmd_output(cmd);
		if (msh_isbuiltin(cmd))
		{		
			msh_exec_builtin(cmd);
			exit(127);
		}	
		cmd->mini->exitcode = execvp(cmd->args[0], cmd->args);
	}
	else
		waitpid(pid, NULL, 0);				
	close_pipes(cmd->mini, pipes);
	swap_pipes((int **)pipes);
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

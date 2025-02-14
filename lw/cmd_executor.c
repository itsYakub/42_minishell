/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:38:58 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/14 15:44:37 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_last_command(t_mini *mini)
{	
	return (mini->current_cmd == mini->cmdc - 1);
}

static void connect_pipes(t_mini *mini, t_pipe pipes[2])
{
	if (mini->cmdc > 1)
	{
		if (is_last_command(mini) || mini->current_cmd != 0)
			dup2(pipes[PREVIOUS_CMD][READ_END], STDIN_FILENO);
		if (mini->current_cmd == 0 || !is_last_command(mini))
			dup2(pipes[CURRENT_CMD][WRITE_END], STDOUT_FILENO);
	}
}

static void close_pipes(t_mini *mini, t_pipe pipes[2])
{
	if (mini->cmdc > 1)
	{
		if (is_last_command(mini) || mini->current_cmd != 0)
			close(pipes[PREVIOUS_CMD][READ_END]);
		if (mini->current_cmd == 0 || !is_last_command(mini))
			close(pipes[CURRENT_CMD][WRITE_END]);
	}
}

static void swap_pipes(int **pipes)
{
	int	*pipe_current;

	pipe_current = pipes[CURRENT_CMD];
	pipes[CURRENT_CMD] = pipes[PREVIOUS_CMD];
	pipes[PREVIOUS_CMD] = pipe_current;
}

static void execute_cmd(t_command *cmd)
{
	static t_pipe 	pipes[2];
	int				pid;
	int				fdinput;
	int				fdoutput;
	char			*line;

	pipe(pipes[CURRENT_CMD]); // error check
	pid = fork(); // error check
	if (0 == pid)
	{
		if (cmd->infilename)
		{
			// close if open?
			if (1 == cmd->inputtype)
			{
				// heredoc creates a temp file, loop appends to it, then continues as normal
				fdinput = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
				while (1)
				{
					line = readline("> ");
					// infilename does double-duty as the dilimiter. We can change this if it's confusing/bad practice
					if (0 == ft_strcmp(cmd->infilename, line))
						break;
					write(fdinput, line, ft_strlen(line));
					write(fdinput, "\n", 1);
				}
				close(fdinput);
				// if infilename is the delimiter, we need to set it back here
				cmd->infilename = ".heredoc";
			}
			fdinput = open(cmd->infilename, O_RDONLY, 0777); // error check		
			dup2(fdinput, STDIN_FILENO);
			close(fdinput);
		}

		connect_pipes(cmd->mini, pipes);

		if (cmd->outfilename)
		{
			// close if open?
			if (cmd->other_outfilenames)
			{
				char **split = ft_split(cmd->other_outfilenames, '\n');
				int	i = -1;
				while (split[++i])
				{
					fdoutput = open(split[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
					close(fdoutput);
				}
				free_stringlist(split);
			}

			if (0 == cmd->outputtype)
				fdoutput = open(cmd->outfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644); // error check
			else
				fdoutput = open(cmd->outfilename, O_WRONLY | O_CREAT | O_APPEND, 0644); // error check
			dup2(fdoutput, STDOUT_FILENO);
			close(fdoutput);
		}

		// builtins
		if (0 == ft_strcmp("pwd", cmd->args[0]))
		{
			ms_pwd(cmd);
			exit(127);
		}
		else
			execvp(cmd->args[0], cmd->args); // change to execve + getpath etc.
	}
	else
		waitpid(pid, NULL, 0);

	close_pipes(cmd->mini, pipes);
	swap_pipes((int **)pipes);
}

int	execute_commands(t_mini *mini)
{
	int	i;
	
	i = -1;
	while (++i < mini->cmdc)
	{
		mini->current_cmd = i;
		execute_cmd(&mini->commands[i]);
	}
	return (1);
}

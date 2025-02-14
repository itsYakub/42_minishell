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

void execute(t_command *cmd)
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

// todo: split execute function, memory checking, replace execvp with execve, plus re-add all the getpath code
// int	main2(int count, char **arguments)
// {
// 	t_mini	mini;

// 	// set to the number of commands
// 	mini.cmd_count = 1;

// 	mini.cmds = malloc(sizeof(t_cmd) * mini.cmd_count);

// 	// setup cmd 1
// 	mini.cmds[0].mini = &mini;

// 	// NULL means no redirect, or set it to a filename, or set it to the heredoc delimiter
// 	mini.cmds[0].infilename = "in";

// 	// set to a filename
// 	mini.cmds[0].outfilename = "out";

// 	// set to 0 for normal input, 1 for heredoc. Ignored if infilename is NULL
// 	mini.cmds[0].inputtype = 0;

// 	// set to 0 for trunc output, 1 for append output, Ignore if outfilename is NULL
// 	mini.cmds[0].outputtype = 0;

// 	// the split command
// 	mini.cmds[0].args = ft_split("cat", ' ');

// 	// setup cmd2, same as above
// 	// mini.cmds[1].mini = &mini;
// 	// mini.cmds[1].infilename = NULL;
// 	// mini.cmds[1].outfilename = "out";
// 	// mini.cmds[1].inputtype = 0;
// 	// mini.cmds[1].outputtype = 0;
// 	// mini.cmds[1].args = ft_split("cat", ' ');

// 	int	i = -1;
// 	while (++i < mini.cmd_count)
// 	{
// 		mini.current_cmd = i;
// 		execute(&mini.cmds[i]);
// 	}
// }

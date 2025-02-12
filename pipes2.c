#include "minishell.h"
void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

void	shell_error(char *message, int exit_code)
{
	if (message)
	{
		write(2, "minishell: ", 11);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	if (exit_code >= 0 && exit_code != 1)
		exit(exit_code);
}

int	get_input(char **line)
{
	char	*buffer;
	char	c;
	int		bytes_read;
	int		i;

	i = 0;
	bytes_read = 0;
	buffer = (char *)malloc(1000);
	if (!buffer)
		return (-1);
	write(0, "> ", 2);
	bytes_read = read(0, &c, 1);
	while (bytes_read && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		bytes_read = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = ft_strdup(buffer);
	free(buffer);
	return (bytes_read);
}

void	better_readline(char *delimiter)
{
	char	*line;
	int		fd[2];
	pid_t	line_reader;

	if (pipe(fd) == -1)
		shell_error("", 1);
	line_reader = fork();
	if(line_reader == 0)
	{
		close(fd[0]);
		while(get_input(&line))
		{
			if(ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
				exit(0);
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
}

int	redirect_output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close (fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_output_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open append");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 append");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_append_redirection(char **tokens, int i)
{
	if (!tokens[i + 1])
	{
		write(STDERR_FILENO,
			"syntax error: expected filename after '>>'\n", 42);
		return (-1);
	}
	if (redirect_output_append(tokens[i + 1]) == -1)
		return (-1);
	tokens[i] = NULL;
	tokens[i + 1] = NULL;
	return (1);
}

static int	handle_heredoc_redirection(char **tokens, int i)
{
	if (!tokens[i + 1])
	{
		write(STDERR_FILENO,
			"syntax error: expected delimiter after '<<'\n", 43);
		return (-1);
	}
	better_readline(tokens[i + 1]);
	tokens[i] = NULL;
	tokens[i + 1] = NULL;
	return (1);
}

static int	handle_output_redirection(char **tokens, int i)
{
	if (!tokens[i + 1])
	{
		write(STDERR_FILENO,
			"syntax error: expected filename after '>'\n", 42);
		return (-1);
	}
	if (redirect_output(tokens[i + 1]) == -1)
		return (-1);
	tokens[i] = NULL;
	tokens[i + 1] = NULL;
	return (1);
}

static int	handle_input_redirection(char **tokens, int i)
{
	if (!tokens[i + 1])
	{
		write(STDERR_FILENO,
			"syntax error: expected filename after '<'\n", 42);
		return (-1);
	}
	if (redirect_input(tokens[i + 1]) == -1)
		return (-1);
	tokens[i] = NULL;
	tokens[i + 1] = NULL;
	return (1);
}

int	handle_redirections(char **tokens)
{
	int	i;
	int	ret;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], ">>", 2) == 0)
			ret = handle_append_redirection(tokens, i);
		else if (ft_strncmp(tokens[i], "<<", 2) == 0)
			ret = handle_heredoc_redirection(tokens, i);
		else if (ft_strchr(tokens[i], '>'))
			ret = handle_output_redirection(tokens, i);
		else if (ft_strchr(tokens[i], '<'))
			ret = handle_input_redirection(tokens, i);
		else
		{
			i++;
			continue ;
		}
		if (ret == -1)
			return (-1);
		i++;
	}
	return (0);
}

static void	find_quote(char *str, int i, int j)
{
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			j++;
		i++;
	}
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = (char *)malloc(ft_strlen(str) + 1);
	find_quote(str, i, j);
	result = malloc(j + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	handle_quotes(char **tokens)
{
	int		i;
	char	*new_str;

	i = 0;
	while (tokens[i])
	{
		new_str = remove_quotes(tokens[i]);
		free(tokens[i]);
		tokens[i] = new_str;
		i++;
	}
}

char	*get_path(char *command, int i, char *temp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_tokens(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tokens(paths);
	return (NULL);
}

static void	cmd_not_found(char **tokens)
{
	write(2, "Command not found: ", 19);
	write(2, tokens[0], ft_strlen(tokens[0]));
	write(2, "\n", 1);
	free_tokens(tokens);
	exit(127);
}

static void	execute_command(char *cmd, char **envp)
{
	char	**tokens;
	char	*path;

	if (0 == ft_strcmp("env", cmd))
	{
		ms_env(NULL);
		exit(127) ;
	}

	tokens = ft_split(cmd, ' ');
	if (handle_redirections(tokens) == -1)
	{
		write(2, "redirection error\n", 18);
		free_tokens(tokens);
		exit(EXIT_FAILURE);
	}
	handle_quotes(tokens);
	path = get_path(tokens[0], 0, NULL);
	if (!path)
		cmd_not_found(tokens);
	execve(path, tokens, envp);
	perror("execve");
	free_tokens(tokens);
	exit(127);
}

static void	handle_child(char *cmd, char **envp, int prev_fd, int *fd)
{
	if (prev_fd != 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (fd[1] != -1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute_command(cmd, envp);
}

static int	fork_and_pipe(char **commands, char **envp, int *prev_fd, int i)
{
	int		fd[2];
	pid_t	pid;

	if (commands[i + 1] && pipe(fd) == -1)
		return (write(2, "pipe error\n", 11), -1);
	pid = fork();
	if (pid < 0)
		return (write(2, "fork error\n", 11), -1);
	if (pid == 0)
		handle_child(commands[i], envp, *prev_fd,
			fd);
	else
	{
		waitpid(pid, NULL, 0);
		//if (WIFEXITED(g_exit_status))
			//g_exit_status = WEXITSTATUS(g_exit_status);
		close(fd[1]);
		if (*prev_fd != 0)
			close(*prev_fd);
		*prev_fd = fd[0];
	}
	return (0);
}

void	handle_pipes(char **commands, char **envp, int i)
{
	int		prev_fd;

	prev_fd = 0;
	i = 0;
	while (commands[i])
	{
		if (fork_and_pipe(commands, envp, &prev_fd, i) == -1)
			break ;
		i++;
	}
	if (prev_fd != 0)
		close(prev_fd);
}
